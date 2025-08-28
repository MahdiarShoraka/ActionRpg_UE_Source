// Mahdiar Shoraka All Rights Reserved


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateSpeed()
{
	APawn* Owner = TryGetPawnOwner();
	if (!IsValid(Owner)) return;

	FVector Velocity = Owner->GetVelocity();
	CurrentSpeed = static_cast<float>(Velocity.Length());
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	// if nullptr -> bIsInCombat = false
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* Owner = TryGetPawnOwner();

	if (!IsValid(Owner)) return;
	if (!bIsInCombat) return;

	CurrentDirection = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());
	
}
