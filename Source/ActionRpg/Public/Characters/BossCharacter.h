// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Characters/EEnemyState.h"
#include "Interfaces/Fighter.h"
#include "BossCharacter.generated.h"

class UStatsComponent;
class UBlackboardComponent;

UCLASS()
class ACTIONRPG_API ABossCharacter : public ACharacter, public IEnemy, public IFighter
{
	GENERATED_BODY()

public:
	ABossCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect);
	
	virtual float GetDamage() override;
	
	virtual void Attack() override;
	
	virtual float GetAnimDuration() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStatsComponent* StatsComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCombatComponent* CombatComp;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	UBlackboardComponent* BlackBoardComp;

};
