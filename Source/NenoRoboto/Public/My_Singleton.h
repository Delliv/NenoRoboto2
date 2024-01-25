// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_CheckPoint.h"
#include "Engine/GameInstance.h"
#include "HAL/Platform.h"
#include "Hook.h"
#include "PortalFrame.h"
#include "My_Singleton.generated.h"

/**
 *
 * https://unreal.blog/ways-to-get-gameinstance-cpp
 * GetWorld()->GetGameInstance()
 * UGameInstanceCreated* GameInstanceRef = Cast<UGameInstanceCreated>(UGameplayStatics::GetGameInstance(GetWorld())
 * UGameInstanceCreated* GameInstanceRef = Cast<UGameInstanceCreated>(GEngine->GetWorld()->GetGameInstance());
 *
 * 
 */

USTRUCT(BlueprintType)
struct FRecollectables{
	GENERATED_BODY()
	FName letra;
	int32 count = 0;
};

UCLASS()
class NENOROBOTO_API UMy_Singleton : public UGameInstance
{
	GENERATED_BODY()
	

public:
	virtual void Init() override;
	//--------------------CheckPoints----------------------
	//Variables
	FVector Saved_Position;
	FVector Saved_Dir;
	int32 Saved_id;
	//Metodos
	UFUNCTION()
		void SaveNewCheckPoint(FVector new_checkPoint, int32 id);

	//--------------------Recollectables----------------------
	//Variables
	UPROPERTY(VisibleAnywhere)
	FRecollectables slots[6]; // R O B O T O
	//Metodos
	UFUNCTION()
		void addRecollectable(const int letra);

	UPROPERTY(VisibleAnywhere)
	bool portal_1_displayed;
	UPROPERTY(VisibleAnywhere)
	bool portal_2_displayed;

	UPROPERTY(VisibleAnywhere)
	APortalFrame* P_1;
	UPROPERTY(VisibleAnywhere)
	APortalFrame* P_2;

	UPROPERTY(VisibleAnywhere)
	bool is_ceiling;
};
