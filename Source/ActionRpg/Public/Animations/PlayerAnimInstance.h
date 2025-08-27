// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class ACTIONRPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	// Copy initialization
	// float CurrentVelocity = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentVelocity{ 0.0f }; // Direct initialization

	UFUNCTION(BlueprintCallable)
	void UpdateVelocity();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInCombat = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentDirection =  0.0f;
};
