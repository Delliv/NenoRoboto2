// Fill out your copyright notice in the Description page of Project Settings.


#include "My_Singleton.h"

#include <string>

void UMy_Singleton::Init(){
	Super::Init();
	slots[0].letra = "R";
	slots[1].letra = "O";
	slots[2].letra = "B";
	slots[3].letra = "O";
	slots[4].letra = "T";
	slots[5].letra = "O";
}

void UMy_Singleton::SaveNewCheckPoint(FVector new_checkPoint, int32 id){

	if(Saved_id <= id){
		Saved_Position = new_checkPoint;
		Saved_id = id;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Take CheckPoint ");
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::FromInt(id));
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "UWU");
}

void UMy_Singleton::addRecollectable(const int letra){
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Inserto Algo");
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, slots[letra].letra.ToString());
	slots[letra].count++;
}
