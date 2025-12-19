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
	// Copy initialization: float CurrentSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentSpeed{ 0.0f }; // Direct initialization

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInCombat = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentDirection =  0.0f;

public:
	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewTargetActorRef);

	UFUNCTION(BlueprintCallable)
	void UpdateDirection();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBlocking = false;
};
