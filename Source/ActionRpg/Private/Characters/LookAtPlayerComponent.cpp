// Mahdiar Shoraka All Rights Reserved


#include "Characters/LookAtPlayerComponent.h"
#include "Kismet/KismetMathLibrary.h"

ULookAtPlayerComponent::ULookAtPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void ULookAtPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void ULookAtPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bCanRotate) return;
	
	AActor* OwnerRef = GetOwner();
	FVector OwnerLocation = OwnerRef->GetActorLocation();
	
	APlayerController* PlayerControllerRef = OwnerRef->GetWorld()->GetFirstPlayerController();
	FVector PlayerLocation = PlayerControllerRef->GetPawn()->GetActorLocation();
	
	// Final Rotation
	FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, PlayerLocation);
	FRotator CurrentRotation = OwnerRef->GetActorRotation();
	
	// Rotation for the next frame
	FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(
		CurrentRotation, 
		DesiredRotation,
		DeltaTime,
		Speed);
	
	// limit rotation to only around z axis 
	FRotator NewYawOnlyRotation(CurrentRotation.Pitch, NewRotation.Yaw, CurrentRotation.Roll);
	
	OwnerRef->SetActorRotation(NewYawOnlyRotation);
}

