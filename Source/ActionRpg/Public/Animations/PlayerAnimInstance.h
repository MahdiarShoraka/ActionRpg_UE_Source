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
	float CurrentVelocity{ 0.0f }; // Direct initialization (only works with newly created variables)

	UFUNCTION(BlueprintCallable)
	void UpdateVelocity();

};
