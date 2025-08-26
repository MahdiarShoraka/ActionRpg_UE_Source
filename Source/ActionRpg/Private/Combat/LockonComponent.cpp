// Mahdiar Shoraka All Rights Reserved


#include "Combat/LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	// 3 same ways of initialization with constructors
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

	CurrentTargetActor = OutResult.GetActor();
	
	Controller->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;
}


void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CurrentTargetActor)) return;

	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FVector TargetLocation = CurrentTargetActor->GetActorLocation();

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation,TargetLocation);
	Controller->SetControlRotation(NewRotation);
}

