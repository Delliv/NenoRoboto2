// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Panel_FinishLane.generated.h"

/**
 * 
 */
UCLASS()
class NENOROBOTO_API UW_Panel_FinishLane : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) // R O B O T O
	class UTextBlock* letra1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* letra2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* letra3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* letra4;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* letra5;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* letra6;
};
