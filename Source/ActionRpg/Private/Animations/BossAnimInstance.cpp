// Mahdiar Shoraka All Rights Reserved


#include "Animations/BossAnimInstance.h"

void UBossAnimInstance::UpdateSpeed()
{
	APawn* Owner = TryGetPawnOwner();
	if (!IsValid(Owner)) return;

	FVector Velocity = Owner->GetVelocity();
	CurrentSpeed = static_cast<float>(Velocity.Length());
}
