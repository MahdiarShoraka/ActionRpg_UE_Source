// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockonComponent,
	OnUpdatedTargetDelegate,
	AActor*, NewTargetActorRef
	);

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

	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;
	
	void EndLockon();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.f);

	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius = 750.f);

	UPROPERTY(EditAnywhere)
	double BreakDistance = 1000.0;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
