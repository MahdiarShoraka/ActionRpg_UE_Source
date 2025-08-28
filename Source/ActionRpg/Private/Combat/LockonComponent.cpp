// Mahdiar Shoraka All Rights Reserved


#include "Combat/LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/Enemy.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();

	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	// 3 same ways of initialization with constructors (stack-based construction using a constructor)
	// FCollisionQueryParams IgnoreParams = FCollisionQueryParams(FName(TEXT("Ignore Collision Params")), false);
	// FCollisionQueryParams IgnoreParams{FName(TEXT("Ignore Collision Params")), false};
	FCollisionQueryParams IgnoreParams(FName(TEXT("Ignore Collision Params")),false, OwnerRef);

	
	// Only the first detected collision (Single)
	bool bHasFoundTarget = GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity, // no rotation,
		ECollisionChannel::ECC_GameTraceChannel1, // Fighter channel,
		Sphere,
		IgnoreParams
	);
	
	if (!bHasFoundTarget) return;

	// UEnemy for validation purposes / IEnemy for defining the actual interface functions
	if (!OutResult.GetActor()->Implements<UEnemy>()) return;

	CurrentTargetActor = OutResult.GetActor();
	
	Controller->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;

	SpringArmComp->TargetOffset = FVector(0, 0, 100);

	IEnemy::Execute_OnSelect(CurrentTargetActor);

	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::EndLockon()
{
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	
	CurrentTargetActor = nullptr;

	// Reset movement components values
	MovementComp->bOrientRotationToMovement = true;	// Rotate the player in the direction they are moving
	MovementComp->bUseControllerDesiredRotation = false;

	// Reset Target Offset value (from StartLockon)
	SpringArmComp->TargetOffset = FVector::ZeroVector;

	Controller->ResetIgnoreLookInput();

	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		EndLockon();
	}
	else
	{
		StartLockon(Radius);
	}
}


void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CurrentTargetActor)) return;

	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FVector TargetLocation = CurrentTargetActor->GetActorLocation();

	double TargetDistance = FVector::Distance(CurrentLocation, TargetLocation);
	if (TargetDistance > BreakDistance)
	{
		EndLockon();
		return;
	}
	
	TargetLocation.Z -= 125;
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation,TargetLocation);
	Controller->SetControlRotation(NewRotation);
}

