// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimator.h"

void UPlayerAnimator::NativeUpdateAnimation(float DeltaSeconds){
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* player = TryGetPawnOwner();
	if(player->IsValidLowLevel()){
		CharSpeed = player->GetVelocity().Size();
	}
}