// Mahdiar Shoraka All Rights Reserved


#include "Combat/EnemyProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

AEnemyProjectile::AEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyProjectile::HandleBeginOverlap(AActor* OtherActor)
{
	APawn* PawnRef = Cast<APawn>(OtherActor);
	if (!PawnRef->IsPlayerControlled()) return;
	
	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();
	
	FTimerHandle DeathTimerHandle;
	GetWorldTimerManager().SetTimer(
		DeathTimerHandle,
		this, 
		&AEnemyProjectile::DestroyProjectile, 
		0.5f);
	
	// avoids multiple collisions per projectile
	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FDamageEvent ProjectileAttackEvent;
	PawnRef->TakeDamage(
		Damage,
		ProjectileAttackEvent,
		PawnRef->GetController(),
		this
		);
}

void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}

