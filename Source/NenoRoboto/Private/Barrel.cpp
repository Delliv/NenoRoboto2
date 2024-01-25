// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "My_Singleton.h"
#include "Barrel.h"

// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	alive = false;
	malla_barril = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	RootComponent = malla_barril;
}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnActorBeginOverlap.AddDynamic(this, &ABarrel::reset_player_pos);
}

void ABarrel::reset_player_pos(AActor* self, AActor* other) {
	if (other->ActorHasTag("Player")) {
		UMy_Singleton* GameInstanceRef = Cast<UMy_Singleton>(UGameplayStatics::GetGameInstance(GetWorld()));

		other->SetActorLocation(GameInstanceRef->Saved_Position);

	}
}
