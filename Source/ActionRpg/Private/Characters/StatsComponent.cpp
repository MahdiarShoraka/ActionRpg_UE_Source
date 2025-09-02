// Mahdiar Shoraka All Rights Reserved


#include "Characters/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

