// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.h"
#include "Spawner_objects.generated.h"

UCLASS()
class NENOROBOTO_API ASpawner_objects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner_objects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditInstanceOnly, Category = "Point1")
	TArray<AActor*> points;
	UPROPERTY(EditInstanceOnly, Category = "Point2")
	AActor* point_2;
	UPROPERTY(EditInstanceOnly, Category ="ActorToSpawn")
	TSubclassOf<AActor> ActorsToSpawn;
	UPROPERTY()
	float time_to_spawn;
	UPROPERTY(EditInstanceOnly)
	TArray<ABarrel*>BarrelsToSpawn;
	UFUNCTION()
	void InitBarrels();

	UFUNCTION()
	void spawn_things();

	UFUNCTION()
	void Update_things();
};
