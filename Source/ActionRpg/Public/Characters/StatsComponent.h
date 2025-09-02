// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/EStat.h"
#include "StatsComponent.generated.h"


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
	
protected:
	virtual void BeginPlay() override;
	
};
