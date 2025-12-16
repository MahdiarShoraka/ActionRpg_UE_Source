// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class ACTIONRPG_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitTemplate;
	
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;
	
public:	
	AEnemyProjectile();
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* OtherActor);
	
	UFUNCTION()	// Necessary for FTimerManager to work
	void DestroyProjectile();

protected:
	virtual void BeginPlay() override;
	
};
