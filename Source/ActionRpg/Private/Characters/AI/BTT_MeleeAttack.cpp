// Mahdiar Shoraka All Rights Reserved


#include "Characters/AI/BTT_MeleeAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Interfaces/Fighter.h"
#include "GameFramework/Character.h"
#include "Characters/EEnemyState.h"

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
	MoveDelegate.BindUFunction(this, "FinishAttackTask");
}

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsFinished = false;
	
	float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"));
	
	AAIController* AIRef = OwnerComp.GetAIOwner();
	
	if (Distance > AttackRadius)
	{
		APawn* PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
		
		FAIMoveRequest MoveRequest(PlayerRef);
		MoveRequest.SetUsePathfinding(true);
		MoveRequest.SetAcceptanceRadius(AcceptableRadius);
		
		AIRef->ReceiveMoveCompleted.AddUnique(MoveDelegate);
		
		AIRef->MoveTo(MoveRequest);
		AIRef->SetFocus(PlayerRef);
	}
	else
	{
		IFighter* FighterRef = Cast<IFighter>(AIRef->GetCharacter());
		FighterRef->Attack();
		
		FTimerHandle AttackTimerHandle;
		AIRef->GetCharacter()->GetWorldTimerManager().SetTimer(
			AttackTimerHandle, 
			this, 
			&UBTT_MeleeAttack::FinishAttackTask, 
			FighterRef->GetAnimDuration(), 
			false);
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_MeleeAttack::FinishAttackTask()
{
	bIsFinished = true;
}

void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"));
	
	AAIController* AIRef = OwnerComp.GetAIOwner();
	
	IFighter* FighterRef = Cast<IFighter>(AIRef->GetCharacter());
	
	if (Distance > FighterRef->GetMeleeRange())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Range);
		AbortTask(OwnerComp, NodeMemory);
		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
		AIRef->StopMovement();
		AIRef->ClearFocus(EAIFocusPriority::Gameplay);
		AIRef->ReceiveMoveCompleted.Remove(MoveDelegate);
	}
	
	if (!bIsFinished) return;
	
	AIRef->ReceiveMoveCompleted.Remove(MoveDelegate);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
