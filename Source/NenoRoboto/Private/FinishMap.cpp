// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishMap.h"

#include "FinishMenu.h"
#include "My_Singleton.h"
#include "W_Panel_FinishLane.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinishMap::AFinishMap(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Cmp_staticmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Cmp_staticmesh;
}

// Called when the game starts or when spawned
void AFinishMap::BeginPlay(){
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AFinishMap::FinishLane);
}

void AFinishMap::FinishLane(AActor* self, AActor* other){
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("He llegado al final!"));
	if(other->ActorHasTag("Player")){
		//FLatentActionInfo LatentInfo;
		//UGameplayStatics::OpenLevel(this, LevelToLoad, true, true, LatentInfo);

		ACharacter* a = Cast<ACharacter>(other);
		if(a != NULL){
			APlayerController* player = a->GetController<APlayerController>();
			if(player != NULL){
				AFinishMenu* hud = player->GetHUD<AFinishMenu>();
				if(hud != NULL){
					hud->panelFinal->SetVisibility(ESlateVisibility::Visible);

					player->SetInputMode(FInputModeUIOnly());
					player->bShowMouseCursor = true;
					
					UMy_Singleton* singleton = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));

					if(singleton != NULL){
						if(singleton->slots[0].count > 0){
							//hud->panelFinal->letra1->SetVisibility(ESlateVisibility::Hidden);
							hud->panelFinal->letra1->SetColorAndOpacity(FSlateColor(FColor::Black)); 
						}
						if(singleton->slots[1].count > 0){
							//hud->panelFinal->letra2->SetVisibility(ESlateVisibility::Hidden);
							hud->panelFinal->letra2->SetColorAndOpacity(FSlateColor(FColor::Black));
						}
						if(singleton->slots[2].count > 0){
							//hud->panelFinal->letra3->SetVisibility(ESlateVisibility::Hidden);
							hud->panelFinal->letra3->SetColorAndOpacity(FSlateColor(FColor::Black));
						}
						if(singleton->slots[3].count > 0){
							//hud->panelFinal->letra4->SetVisibility(ESlateVisibility::Hidden);
							hud->panelFinal->letra4->SetColorAndOpacity(FSlateColor(FColor::Black));
						}
						if(singleton->slots[4].count > 0){
							//hud->panelFinal->letra5->SetVisibility(ESlateVisibility::Hidden);
							hud->panelFinal->letra5->SetColorAndOpacity(FSlateColor(FColor::Black));
						}
						if(singleton->slots[5].count > 0){
							//hud->panelFinal->letra6->SetVisibility(ESlateVisibility::Hidden);
							hud->panelFinal->letra6->SetColorAndOpacity(FSlateColor(FColor::Black));
						}
					}
				}
			}
		}
		//UGameplayStatics::OpenLevel(this, LevelToLoad);
	}
}

