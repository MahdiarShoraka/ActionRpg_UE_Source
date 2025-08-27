// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"


class USpringArmComponent;
class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

	// variables not defined in any section are automatically private

	ACharacter* OwnerRef;
	APlayerController* Controller;
	UCharacterMovementComponent* MovementComp;

	USpringArmComponent* SpringArmComp;
public:	
	ULockonComponent();
	
	AActor* CurrentTargetActor;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.f);
	
	void EndLockon();

	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius = 750.f);

	UPROPERTY(EditAnywhere)
	double BreakDistance = 1000.0;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
