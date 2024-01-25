// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishMap.generated.h"

UCLASS()
class NENOROBOTO_API AFinishMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishMap();

	UPROPERTY(EditInstanceOnly)
		FName LevelToLoad;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Model)
		UStaticMeshComponent* Cmp_staticmesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION()
			void FinishLane(AActor* self, AActor* other);
};
