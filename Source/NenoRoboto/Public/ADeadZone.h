// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADeadZone.generated.h"

UCLASS()
class NENOROBOTO_API AADeadZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AADeadZone();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Model)
	UStaticMeshComponent* Cmp_staticmesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
			void deletSomething(AActor* self, AActor* other);

};
