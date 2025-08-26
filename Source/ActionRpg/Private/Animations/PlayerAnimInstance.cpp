// Mahdiar Shoraka All Rights Reserved


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateVelocity()
{
	APawn* Owner = TryGetPawnOwner();
	if (!IsValid(Owner)) return;

	FVector Velocity = Owner->GetVelocity();
	CurrentVelocity = static_cast<float>(Velocity.Length());
}
