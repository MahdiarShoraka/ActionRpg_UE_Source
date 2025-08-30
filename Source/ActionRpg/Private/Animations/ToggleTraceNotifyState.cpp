// Mahdiar Shoraka All Rights Reserved


#include "Animations/ToggleTraceNotifyState.h"
#include "Combat/TraceComponent.h"

void UToggleTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UTraceComponent* TraceComp = MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>();

	if (!IsValid(TraceComp)) return;

	TraceComp->bIsAttacking = true;
}

void UToggleTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UTraceComponent* TraceComp = MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>();

	if (!IsValid(TraceComp)) return;

	TraceComp->bIsAttacking = false;
}
