// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalFrame.h"

// Sets default values
APortalFrame::APortalFrame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	frame_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HookMesh"));
	spawn_point = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint"));

	RootComponent = frame_mesh;
	spawn_point->SetupAttachment(frame_mesh);
}

// Called when the game starts or when spawned
void APortalFrame::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalFrame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

