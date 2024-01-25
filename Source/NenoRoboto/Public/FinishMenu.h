// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FinishMenu.generated.h"

/**
 * 
 */
UCLASS()
class NENOROBOTO_API AFinishMenu : public AHUD
{
	GENERATED_BODY()

	void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel Finish Lane")
	TSubclassOf<UUserWidget> panel;

	class UW_Panel_FinishLane* panelFinal;
};
