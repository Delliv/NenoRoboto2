// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalFrame.h"
#include "Hook.generated.h"

UCLASS()
class NENOROBOTO_API AHook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHook();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh hook")
	UStaticMeshComponent* hook_mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Alive)
	bool is_alive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Speed)
	float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Portal)
	int portal_;

	UFUNCTION()
	void LaunchHook(FVector player_forward);
	
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//void Overlap(AActor* self, AActor* other);
	

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Mesh Portal")
	TSubclassOf<APortalFrame> frame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Portal 2")
	TSubclassOf<APortalFrame> frame_portal_2;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

