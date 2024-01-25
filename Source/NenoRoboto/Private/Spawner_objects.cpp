// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner_objects.h"

// Sets default values
ASpawner_objects::ASpawner_objects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner_objects::BeginPlay()
{
	Super::BeginPlay();
	InitBarrels();
	spawn_things();
}

// Called every frame
void ASpawner_objects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time_to_spawn += DeltaTime;
	Update_things();
}

void ASpawner_objects::InitBarrels() {

	for (int i = 0; i < 6; i++) {
	
			BarrelsToSpawn[i] = GetWorld()->SpawnActor<ABarrel>(ActorsToSpawn, points[i]->GetActorLocation(), FRotator(0, 0, 90));
			BarrelsToSpawn[i]->alive = false;
			BarrelsToSpawn[i]->SetActorHiddenInGame(true);
			//BarrelsToSpawn[i]->malla_barril->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			BarrelsToSpawn[i]->SetActorTickEnabled(false);	
	}
}

void ASpawner_objects::spawn_things() {
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Asi si si si"));
	//if (ActorsToSpawn) {
		//GetWorld()->SpawnActor<AActor>(ActorsToSpawn, point_1, FRotator(0, 0, 0));
		//GetWorld()->SpawnActor<AActor>(ActorsToSpawn, point_2, FRotator(0, 0, 0));
	for(int i=0;i<6;i++)
	{
		BarrelsToSpawn[i]->alive = true;
		BarrelsToSpawn[i]->SetActorHiddenInGame(false);
		//BarrelsToSpawn[i]->malla_barril->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BarrelsToSpawn[i]->SetActorTickEnabled(true);
	}

}

void ASpawner_objects::Update_things()
{
	for(int i=0;i<6;i++){
		if(BarrelsToSpawn[i]->GetActorLocation().Z < -1)
		{
			//Engine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Ay me cai"));
			BarrelsToSpawn[i]->SetActorLocation(points[i]->GetActorLocation());
			UStaticMeshComponent* a = BarrelsToSpawn[i]->malla_barril;
			a->SetPhysicsAngularVelocityInDegrees(FVector(0,0,0));
			a->SetPhysicsLinearVelocity(FVector(0,0,0));
			BarrelsToSpawn[i]->SetActorRotation(FRotator(0,0,90));
		}
	}
}

