// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

	// variables not defined in any section are automatically private

	ACharacter* OwnerRef;
	APlayerController* Controller;
	class UCharacterMovementComponent* MovementComp;
	
public:	
	ULockonComponent();
	
	AActor* CurrentTargetActor;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.f);
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
