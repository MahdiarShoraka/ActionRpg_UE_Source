// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UEnemyProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyProjectileComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(FName ComponentName, TSubclassOf<AActor> ProjectileClass);
	
protected:
	virtual void BeginPlay() override;
	
};
