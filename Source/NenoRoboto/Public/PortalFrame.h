// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalFrame.generated.h"

UCLASS()
class NENOROBOTO_API APortalFrame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalFrame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh hook")
	UStaticMeshComponent* frame_mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn Point")
	UStaticMeshComponent* spawn_point;
	UPROPERTY(VisibleAnywhere)
	bool ceiling_;
};
