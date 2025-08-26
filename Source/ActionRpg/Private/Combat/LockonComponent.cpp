// Mahdiar Shoraka All Rights Reserved


#include "Combat/LockonComponent.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ULockonComponent::StartLockon()
{
	FHitResult OutResult;
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(750.f);

	// 3 same ways of initialization with constructors
	// FCollisionQueryParams IgnoreParams = FCollisionQueryParams(FName(TEXT("Ignore Collision Params")), false);
	// FCollisionQueryParams IgnoreParams{FName(TEXT("Ignore Collision Params")), false};
	FCollisionQueryParams IgnoreParams(FName(TEXT("Ignore Collision Params")),false);

	
	// Only the first detected collision (Single)
	GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity, // no rotation,
		ECollisionChannel::ECC_GameTraceChannel1, // Fighter channel,
		Sphere
	);
	UE_LOG(LogTemp, Warning, TEXT("Lockon Started..."));
}


void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

