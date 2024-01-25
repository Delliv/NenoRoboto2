// Copyright Epic Games, Inc. All Rights Reserved.

#include "NenoRobotoCharacter.h"
#include "NenoRobotoProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "Hook.h"
#include "InRecollectable.h"
#include "My_Singleton.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ANenoRobotoCharacter

ANenoRobotoCharacter::ANenoRobotoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);
}

void ANenoRobotoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	
	Mesh1P->SetHiddenInGame(false, true);
	
	Cast<APlayerController>(GetController())->SetInputMode(FInputModeGameOnly());
	// Binding collisions
	OnActorBeginOverlap.AddDynamic(this, &ANenoRobotoCharacter::BeginOverlap);
}

void ANenoRobotoCharacter::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);

	if(GetMovementComponent()->IsFalling()){
		coyote_Timer+=DeltaSeconds;
		if(wantJump){future_Timer+=DeltaSeconds;}
	}else{
		coyote_Timer = 0.0f;
		jumped = false;
	}

	if(wantJump){
		DoJump();
	}
	
	if(future_Timer > futureTime){
		wantJump = false;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANenoRobotoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ANenoRobotoCharacter::myJumpFunction);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ANenoRobotoCharacter::OnFire);
	PlayerInputComponent->BindAction("FireRight", IE_Pressed, this, &ANenoRobotoCharacter::OnFire_Right);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ANenoRobotoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANenoRobotoCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANenoRobotoCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANenoRobotoCharacter::LookUpAtRate);

	// Bind Sprint events
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ANenoRobotoCharacter::StartSprint);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ANenoRobotoCharacter::EndSprint);
}

void ANenoRobotoCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (GameInstanceRef) {
				

				if (GameInstanceRef->P_1 != NULL) {
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Borro el portal que habia"));
					GameInstanceRef->P_1->Destroy();
					GameInstanceRef->P_1 = NULL;
				}
				//other->Destroy();
			}

			// spawn the projectile at the muzzle
			AHook* player_hook = World->SpawnActor<AHook>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if(player_hook != nullptr){
				player_hook->portal_ = 0;
				player_hook->LaunchHook(FP_Gun->GetRightVector());
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation()); // <----- Sonido pistola.
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void ANenoRobotoCharacter::OnFire_Right()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Disparo con la derecha we"));

	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (GameInstanceRef) {


				if (GameInstanceRef->P_2 != NULL) {
					//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Borro el portal que habia"));
					GameInstanceRef->P_2->Destroy();
					GameInstanceRef->P_2 = NULL;
				}
				//other->Destroy();
			}

			// spawn the projectile at the muzzle
			AHook* player_hook = World->SpawnActor<AHook>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (player_hook != nullptr) {
				player_hook->portal_ = 1;
				player_hook->LaunchHook(FP_Gun->GetRightVector());
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation()); // <----- Sonido pistola.
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void ANenoRobotoCharacter::MoveForward(float Value)
{
	if (Value != 0.0f){
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ANenoRobotoCharacter::MoveRight(float Value)
{
	if (Value != 0.0f){
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ANenoRobotoCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANenoRobotoCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ANenoRobotoCharacter::myJumpFunction(){
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("Intento Saltar"));
	wantJump = true;
	future_Timer = 0.0f;
	//if(!jumped){
	//	DoJump();
	//}
}

void ANenoRobotoCharacter::DoJump(){
	if(coyote_Timer < CoyoteTime && !jumped){
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Salto"));
		jumped = true;
		wantJump = false;
		ACharacter::Jump();
	}
}

void ANenoRobotoCharacter::StartSprint(){
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, TEXT("Corroooooo"));
	GetCharacterMovement()->MaxWalkSpeed *= ExtraSpeedSprint;
}

void ANenoRobotoCharacter::EndSprint(){
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, TEXT("Dejo De correr"));
	GetCharacterMovement()->MaxWalkSpeed /= ExtraSpeedSprint;
}

void ANenoRobotoCharacter::BeginOverlap(AActor* self, AActor* other){
	if (other->GetClass()->ImplementsInterface(UInRecollectable::StaticClass())) {
		int id = IInRecollectable::Execute_TakeObject(other, this);

		UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
		if(GameInstanceRef){
			GameInstanceRef->addRecollectable(id);
			other->Destroy();
		}
	}
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, TEXT("Aweo"));

	if (other->ActorHasTag("portal_1")) {
		UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
		//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, TEXT("Toqueteo el portal 1"));
       
		//SetActorRotation(GameInstanceRef->P_2->GetActorRotation());
		if (GameInstanceRef->portal_2_displayed) {
		//AddControllerYawInput(500);
		if (!GameInstanceRef->P_2->ceiling_) {
			FRotator f = GameInstanceRef->P_2->GetActorRotation();
			f.Pitch = 0;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("B"));
			
			//FirstPersonCameraComponent->bUsePawnControlRotation = false;
			//PlayerController g = Cast<APlayerController>(GetController());
			GetController()->SetControlRotation(f);
			//bUseControllerRotationPitch = false;
			bUseControllerRotationYaw = false;
			SetActorRotation(f);
		}
		//FaceRotation(f);
		//SetActorRelativeRotation(GameInstanceRef->P_2->GetActorRotation());
		
			SetActorLocation(GameInstanceRef->P_2->spawn_point->GetComponentLocation()/* + (GameInstanceRef->P_2->GetActorForwardVector() * 100)*/);
		
		//FirstPersonCameraComponent->bUsePawnControlRotation = true;
		bUseControllerRotationYaw = true;
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, GameInstanceRef->P_2->spawn_point->GetComponentLocation().ToString());
		}
	}
	
	if (other->ActorHasTag("portal_2")) {
		UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GameInstanceRef->portal_1_displayed) {
			//FirstPersonCameraComponent->bUsePawnControlRotation = false;
			
			if (!GameInstanceRef->P_1->ceiling_) {
				FRotator f = GameInstanceRef->P_1->GetActorRotation();
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("A"));
                f.Pitch = 0;
				GetController()->SetControlRotation(f);
				//bUseControllerRotationPitch = false;
				//SetActorRelativeRotation(GameInstanceRef->P_1->GetActorRotation());
				//FRotator f = GetActorRotation();
				bUseControllerRotationYaw = false;
				SetActorRotation(f);
			}
			//FaceRotation(GameInstanceRef->P_1->GetActorRotation());
			//APlayerController::AController SetControlRotation(GameInstanceRef->P_1->GetActorRotation());
			//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, f.ToString());
			//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, GameInstanceRef->P_1->spawn_point->GetComponentLocation().ToString());
		
				SetActorLocation(GameInstanceRef->P_1->spawn_point->GetComponentLocation()/* + (GameInstanceRef->P_1->GetActorForwardVector() * 100)*/);
		
			//FirstPersonCameraComponent->bUsePawnControlRotation = true;
			bUseControllerRotationYaw = true;
		}
	}
}
