// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NenoRobotoHUD.generated.h"

UCLASS()
class ANenoRobotoHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANenoRobotoHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

