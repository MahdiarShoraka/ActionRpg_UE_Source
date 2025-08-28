// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "MainCharacter.generated.h"

class UPlayerAnimInstance;

UCLASS()
class ACTIONRPG_API AMainCharacter : public ACharacter, public IMainPlayer
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UPlayerAnimInstance* PlayerAnimInstance;
	
public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
