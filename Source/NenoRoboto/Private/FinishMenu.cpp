// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishMenu.h"

#include "W_Panel_FinishLane.h"
#include "Blueprint/UserWidget.h"

void AFinishMenu::BeginPlay(){
	Super::BeginPlay();

	panelFinal = CreateWidget<UW_Panel_FinishLane>(GetOwningPlayerController(), panel);
	panelFinal->AddToViewport();
	panelFinal->SetVisibility(ESlateVisibility::Hidden);
}
