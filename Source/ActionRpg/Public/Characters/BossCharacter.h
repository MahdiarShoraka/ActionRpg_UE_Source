// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "BossCharacter.generated.h"

class UStatsComponent;

UCLASS()
class ACTIONRPG_API ABossCharacter : public ACharacter, public IEnemy
{
	GENERATED_BODY()

public:
	ABossCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStatsComponent* StatsComp;

protected:
	virtual void BeginPlay() override;

};
