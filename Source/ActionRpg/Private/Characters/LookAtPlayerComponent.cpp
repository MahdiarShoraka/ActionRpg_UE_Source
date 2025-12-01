// Mahdiar Shoraka All Rights Reserved


#include "Characters/LookAtPlayerComponent.h"
#include "Kismet/KismetMathLibrary.h"

ULookAtPlayerComponent::ULookAtPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void ULookAtPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void ULookAtPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* OwnerRef = GetOwner();
	FVector OwnerLocation = OwnerRef->GetActorLocation();
	
	APlayerController* PlayerControllerRef = OwnerRef->GetWorld()->GetFirstPlayerController();
	FVector PlayerLocation = PlayerControllerRef->GetPawn()->GetActorLocation();
	
	FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, PlayerLocation);
	FRotator CurrentRotation = OwnerRef->GetActorRotation();
	
	FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(
		CurrentRotation, 
		DesiredRotation,
		GetWorld()->DeltaTimeSeconds,
		Speed);
	
	// Rotation around z axis only 
	FRotator NewYawOnlyRotation(CurrentRotation.Pitch, NewRotation.Yaw, CurrentRotation.Roll);
	
	OwnerRef->SetActorRotation(NewYawOnlyRotation);
}

