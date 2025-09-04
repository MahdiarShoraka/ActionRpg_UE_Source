// Mahdiar Shoraka All Rights Reserved


#include "Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/MainPlayer.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner<ACharacter>();
}

void UCombatComponent::ComboAttack()
{
	// Note:In interfaces, U class is used for validation, I class is used for functions inside the interface
	if (Owner->Implements<UMainPlayer>())
	{
		IMainPlayer* IPlayerRef = Cast<IMainPlayer>(Owner);

		if (IPlayerRef && !IPlayerRef->HasEnoughStamina(StaminaCost)) return;
	}
	
	if (!bCanAttack) return;
	bCanAttack = false;
	
	Owner->PlayAnimMontage(AttackAnimations[ComboCounter]);

	ComboCounter++;

	int MaxCombo = AttackAnimations.Num();

	ComboCounter = UKismetMathLibrary::Wrap(
		ComboCounter,
		-1,	// exclusive
		MaxCombo - 1  // inclusive
		);
	
	OnAttackPerformedDelegate.Broadcast(StaminaCost);
}

void UCombatComponent::HandleResetAttack()
{
	bCanAttack = true;
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

