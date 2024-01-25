// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "A_CheckPoint.generated.h"

UCLASS()
class NENOROBOTO_API AA_CheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_CheckPoint();

	//UPROPERTY()
	//	UBoxComponent* Trigger;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Model)
		UStaticMeshComponent* Trigger;
	
		
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite, Category="_Spawn Info")
		int32 CheckPoint_ID; // Para indicar el orden de los check points.
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
