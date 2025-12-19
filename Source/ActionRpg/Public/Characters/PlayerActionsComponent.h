// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PlayerActionsComponent.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature,
	UPlayerActionsComponent,
	OnSprintDelegate,
	float, Cost);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnRollSignature,
	UPlayerActionsComponent,
	OnRollDelegate,
	float, Cost);

class UCharacterMovementComponent;
class IMainPlayer;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerActionsComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void Walk();

	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnRollSignature OnRollDelegate;
	
protected:
	virtual void BeginPlay() override;

private:
	ACharacter* CharacterRef;

	IMainPlayer* IPlayerRef;

	UCharacterMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere)
	float SprintCost = 0.1f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 500.f;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* RollAnimMontage;
	
	UPROPERTY(EditAnywhere)
	float RollCost = 5.0f;
	
	bool bIsRollActive = false;
};
