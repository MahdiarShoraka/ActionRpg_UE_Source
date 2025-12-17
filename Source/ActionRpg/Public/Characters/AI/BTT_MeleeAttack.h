// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UBTT_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float AttackRadius = 250.f;
	
	UPROPERTY(EditAnywhere)
	float AcceptableRadius = 150.f;
	
	FScriptDelegate MoveDelegate;
	
	bool bIsFinished = false;
	
public:
	
	UBTT_MeleeAttack();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UFUNCTION()
	void FinishAttackTask();
	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
