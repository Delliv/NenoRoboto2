// Fill out your copyright notice in the Description page of Project Settings.


#include "RecollectableLetra.h"

#include "My_Singleton.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARecollectableLetra::ARecollectableLetra()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cmp_staticmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	RootComponent = Cmp_staticmesh;
}

// Called when the game starts or when spawned
void ARecollectableLetra::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARecollectableLetra::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	contador += DeltaTime * 2.0f;
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y,GetActorLocation().Z + (sin(contador) * 0.2f )));
	if(contador > 4000000){
		contador = 0;
	}
}

int ARecollectableLetra::TakeObject_Implementation(AActor* interactor){
	
	return idLetra;
}

