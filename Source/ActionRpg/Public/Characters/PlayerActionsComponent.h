// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"


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
};
