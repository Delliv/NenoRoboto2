// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimator.generated.h"

/**
 * 
 */
UCLASS()
class NENOROBOTO_API UPlayerAnimator : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AnimParams")
	float CharSpeed;

	void NativeUpdateAnimation(float DeltaSeconds) override;
};
