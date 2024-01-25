// Fill out your copyright notice in the Description page of Project Settings.

#include "PortalFrame.h"
#include "Hook.h"
#include "My_Singleton.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHook::AHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hook_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HookMesh"));
	//frame = CreateDefaultSubobject<APortalFrame>(TEXT("FrameMesh"));
	RootComponent = hook_mesh;
	//portal_ = 1;
	is_alive = false;
	
}

void AHook::LaunchHook(FVector f)
{
	this->hook_mesh->AddImpulse(f * speed);
}

void AHook::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	//hook_mesh->SetSimulatePhysics(false);
    	FActorSpawnParameters ActorSpawnParams;
        ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        //other->GetComponents()
		

    	FRotator a = Hit.ImpactNormal.Rotation();
    	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Hola"));
        //APortalFrame* portal_hook = GetWorld()->SpawnActor<APortalFrame>(frame,hook_mesh->GetComponentLocation(),a,ActorSpawnParams);
    	//portal_hook->SetActorRotation(a);
    	hook_mesh->DestroyComponent();
		UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GameInstanceRef) {
			if (portal_ == 0) {
				APortalFrame* portal_hook_1 = GetWorld()->SpawnActor<APortalFrame>(frame, hook_mesh->GetComponentLocation(), a, ActorSpawnParams);
				portal_hook_1->SetActorRotation(a);
				GameInstanceRef->portal_1_displayed = true;
				GameInstanceRef->P_1 = portal_hook_1;

				if (OtherActor->ActorHasTag("ceiling")) {
					GameInstanceRef->P_1->ceiling_ = true;
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Its the ceiling"));
				}
				else {
					GameInstanceRef->P_1->ceiling_ = false;
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Its not the ceiling"));
				}
			}
			if (portal_ == 1) {
				APortalFrame* portal_hook_2 = GetWorld()->SpawnActor<APortalFrame>(frame_portal_2, hook_mesh->GetComponentLocation(), a, ActorSpawnParams);
				portal_hook_2->SetActorRotation(a);
				GameInstanceRef->portal_2_displayed = true;
				GameInstanceRef->P_2 = portal_hook_2;

				if (OtherActor->ActorHasTag("ceiling")) {
					GameInstanceRef->P_2->ceiling_ = true;
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Its the ceiling"));
				}
				else {
					GameInstanceRef->P_2->ceiling_ = false;
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Its not the ceiling"));
				}
			}
			
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::FromInt(GameInstanceRef->portal_1_displayed));
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::FromInt(GameInstanceRef->portal_2_displayed));

			//other->Destroy();
		}
}
/*oid AHook::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//hook_mesh->SetSimulatePhysics(false);
	FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    //other->GetComponents()
    
	FRotator a = SweepResult.ImpactNormal.Rotation();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, a.ToString());
    APortalFrame* portal_hook = GetWorld()->SpawnActor<APortalFrame>(frame,hook_mesh->GetComponentLocation(),a,ActorSpawnParams);
	portal_hook->SetActorRotation(a);
	hook_mesh->DestroyComponent();
}
/*
void AHook::Overlap(AActor* self, AActor* other)
{
	//AHook* a = Cast<AHook>self;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Inserto Algo");
	//a->hook_mesh->SetSimulatePhysics((false));
	hook_mesh->SetSimulatePhysics(false);
	hook_mesh->DestroyComponent();
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//other->GetComponents()
	//APortalFrame* player_hook = GetWorld()->SpawnActor<APortalFrame>(frame, self->GetActorLocation(), , ActorSpawnParams);
	
}
*/
// Called when the game starts or when spawned
void AHook::BeginPlay()
{
	Super::BeginPlay();
	hook_mesh->OnComponentHit.AddDynamic(this, &AHook::OnComponentHit);
}

// Called every frame
void AHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


