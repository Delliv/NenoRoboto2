// Fill out your copyright notice in the Description page of Project Settings.


#include "ADeadZone.h"

#include "My_Singleton.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AADeadZone::AADeadZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Cmp_staticmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Cmp_staticmesh;
}

// Called when the game starts or when spawned
void AADeadZone::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AADeadZone::deletSomething);
}

void AADeadZone::deletSomething(AActor* self, AActor* other) {
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Muero"));
	//other->Destroy();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, other->GetName());
	if(other->ActorHasTag("Player")){
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Muero"));
		UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, GameInstanceRef->Saved_Position.ToString());
		//Lechuga con tomate
		other->SetActorLocation(GameInstanceRef->Saved_Position);
		//other->location
	}
}


