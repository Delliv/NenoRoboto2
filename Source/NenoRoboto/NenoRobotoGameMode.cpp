// Copyright Epic Games, Inc. All Rights Reserved.

#include "NenoRobotoGameMode.h"
#include "NenoRobotoHUD.h"
#include "NenoRobotoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANenoRobotoGameMode::ANenoRobotoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANenoRobotoHUD::StaticClass();
}
