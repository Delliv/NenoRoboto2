// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InRecollectable.h"
#include "GameFramework/Actor.h"
#include "RecollectableLetra.generated.h"

UCLASS()
class NENOROBOTO_API ARecollectableLetra : public AActor, public IInRecollectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecollectableLetra();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Model)
	UStaticMeshComponent* Cmp_staticmesh;

	UPROPERTY(EditInstanceOnly)
	int idLetra;

	UPROPERTY(EditAnywhere)
	float oscilacion = 2.0f;

	float contador = 0.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//void Taked();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
		int TakeObject(AActor* interactor);
		int TakeObject_Implementation(AActor* interactor);
};
