// Mahdiar Shoraka All Rights Reserved


#include "Combat/EnemyProjectileComponent.h"

UEnemyProjectileComponent::UEnemyProjectileComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UEnemyProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEnemyProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEnemyProjectileComponent::SpawnProjectile(FName ComponentName, TSubclassOf<AActor> ProjectileClass)
{
	USceneComponent* SpawnPointComp = Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(ComponentName));
	FVector SpawnLocation = SpawnPointComp->GetComponentLocation();
	GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation);
}

