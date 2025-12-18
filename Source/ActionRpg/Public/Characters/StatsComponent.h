// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/EStat.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnHealthPercentUpdateSignature,
	UStatsComponent, 
	OnHealthPercentUpdateDelegate,
	float, Percentage);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnStaminaPercentUpdateSignature,
	UStatsComponent, 
	OnStaminaPercentUpdateDelegate,
	float, Percentage);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(
	FOnZeroHealthSignature,
	UStatsComponent,
	OnZeroHealthDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatsComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStat>, float> Stats;	// Key : Enum of type EStat, Value: float

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float Damage);

	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float Cost);

	UFUNCTION(BlueprintCallable)
	void RegenStamina();

	UFUNCTION()
	void EnableRegen();
	
	UFUNCTION(BlueprintPure)
	float GetStatPercentage(EStat Current, EStat Max);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthPercentUpdateSignature OnHealthPercentUpdateDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnStaminaPercentUpdateSignature OnStaminaPercentUpdateDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnZeroHealthSignature OnZeroHealthDelegate;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	double StaminaRegenRate = 10.0;

	UPROPERTY(VisibleAnywhere)
	bool bCanRegen = true;

	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration = 2.0f;
	
};
