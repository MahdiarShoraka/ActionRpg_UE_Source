// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UBTT_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_RangeAttack();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;
	
	double Threshold = 0.9;
};
