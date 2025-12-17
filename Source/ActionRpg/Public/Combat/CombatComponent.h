// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature,	// Event name (standard practice to prefix with FOn and postfix with Signature)
	UCombatComponent,	//	class that holds the event
	OnAttackPerformedDelegate,	// event name for when the event info is stored in the same class (standard practice to start with On and end with Delegate)
	float, Amount	// passed-in arg type, passed-in arg name
	);

class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ComboAttack();

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

	// All events should be in public
	UPROPERTY(BlueprintAssignable)
	FOnAttackPerformedSignature OnAttackPerformedDelegate;
	
	void RandomAttack();
	
	float AnimDuration;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AttackAnimations;

	ACharacter* Owner;

	UPROPERTY(VisibleAnywhere)
	int ComboCounter = 0;

	UPROPERTY(VisibleAnywhere)
	bool bCanAttack = true;

	UPROPERTY(EditAnywhere)
	float StaminaCost = 5.0f;
};
