// Mahdiar Shoraka All Rights Reserved


#include "Characters/PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


UPlayerActionsComponent::UPlayerActionsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	MovementComp = CharacterRef->GetCharacterMovement();

	if (!CharacterRef->Implements<UMainPlayer>()) return;

	IPlayerRef = Cast<IMainPlayer>(CharacterRef);
}


// Called every frame
void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPlayerActionsComponent::Sprint()
{
	if (!IPlayerRef->HasEnoughStamina(SprintCost))
	{
		Walk();
		return;
	}
	if (MovementComp->Velocity.Equals(FVector::ZeroVector, 1)) return;
	
	MovementComp->MaxWalkSpeed = SprintSpeed;

	OnSprintDelegate.Broadcast(SprintCost);
}

void UPlayerActionsComponent::Walk()
{
	MovementComp->MaxWalkSpeed = WalkSpeed;
}

void UPlayerActionsComponent::Roll()
{
	if (bIsRollActive || !IPlayerRef->HasEnoughStamina(RollCost)) return;
	
	bIsRollActive = true;
	
	OnRollDelegate.Broadcast(RollCost);
	
	FVector Direction = CharacterRef->GetCharacterMovement()->Velocity.Length() < 1 ? 
	CharacterRef->GetActorForwardVector() : CharacterRef->GetLastMovementInputVector();
	
	FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(Direction);
	CharacterRef->SetActorRotation(NewRotation);
	
	float AnimDuration = CharacterRef->PlayAnimMontage(RollAnimMontage);
	
	FTimerHandle RollTimerHandle;
	CharacterRef->GetWorldTimerManager().SetTimer(
		RollTimerHandle, 
		this, 
		&UPlayerActionsComponent::FinishRollAnim, 
		AnimDuration, false);
}

void UPlayerActionsComponent::FinishRollAnim()
{
	bIsRollActive = false;
}

