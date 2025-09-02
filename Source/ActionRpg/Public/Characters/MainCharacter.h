// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "Interfaces/Fighter.h"
#include "MainCharacter.generated.h"

class UPlayerAnimInstance;
class ULockonComponent;
class UStatsComponent;
class UCombatComponent;
class UTraceComponent;
class UBlockComponent;
class UPlayerActionsComponent;

UCLASS()
class ACTIONRPG_API AMainCharacter : public ACharacter, public IMainPlayer, public IFighter
{
	GENERATED_BODY()

public:
	AMainCharacter();

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() override;

	virtual bool HasEnoughStamina(float Cost) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStatsComponent* StatsComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ULockonComponent* LockonComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCombatComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTraceComponent* TraceComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlockComponent* BlockComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPlayerActionsComponent* PlayerActionsComp;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UPlayerAnimInstance* PlayerAnimInstance;
	
};
