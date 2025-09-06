// Mahdiar Shoraka All Rights Reserved


#include "Characters/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include  "Kismet/KismetSystemLibrary.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UStatsComponent::ReduceHealth(float Damage)
{
	if (Stats[EStat::Health] <= 0) return;

	Stats[EStat::Health] -= Damage;
	Stats[EStat::Health] = UKismetMathLibrary::FClamp(
		Stats[EStat::Health],
		0,
		Stats[EStat::MaxHealth]);
}

void UStatsComponent::ReduceStamina(float Cost)
{
	Stats[EStat::Stamina] -= Cost;
	Stats[EStat::Stamina] = UKismetMathLibrary::FClamp(
		Stats[EStat::Stamina],
		0,
		Stats[EStat::MaxStamina]);

	bCanRegen = false;

	FLatentActionInfo FunctionInfo(0, 100, TEXT("EnableRegen"), this);
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), StaminaDelayDuration, FunctionInfo);
}

void UStatsComponent::RegenStamina()
{
	if (!bCanRegen) return;
	
	// use interpolation to avoid instant full regeneration
	Stats[EStat::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStat::Stamina],
		Stats[EStat::MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRegenRate);
}

void UStatsComponent::EnableRegen()
{
	bCanRegen = true;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

