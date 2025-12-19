// Mahdiar Shoraka All Rights Reserved


#include "Characters/BossCharacter.h"
#include "Characters/StatsComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/CombatComponent.h"
#include "Characters/MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/MainPlayer.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
}

void ABossCharacter::DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect)
{
	EEnemyState CurrentState = static_cast<EEnemyState>(BlackBoardComp->GetValueAsEnum("CurrentState"));	

	if (DetectedPawn != PawnToDetect || CurrentState != EEnemyState::Idle) return;

	BlackBoardComp->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Range);
}

float ABossCharacter::GetDamage()
{
	return StatsComp->Stats[EStat::Strength];
}

void ABossCharacter::Attack()
{
	CombatComp->RandomAttack();
}

float ABossCharacter::GetAnimDuration()
{
	return CombatComp->AnimDuration;
}

float ABossCharacter::GetMeleeRange()
{
	return StatsComp->Stats[EStat::MeleeRange];
}

void ABossCharacter::HandlePlayerDeath()
{
	ControllerRef->GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::GameOver);
}

void ABossCharacter::HandleDeath()
{
	float AnimDuration = PlayAnimMontage(DeathAnim);
	
	ControllerRef->GetBrainComponent()->StopLogic("Defeated");
	
	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DestroyTimerHandle, 
		this, 
		&ABossCharacter::FinishDeathAnim, 
		AnimDuration, 
		false);
	
	IMainPlayer* PlayerRef = Cast<IMainPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerRef) return;
	
	PlayerRef->EndLockonWithActor(this);
}

void ABossCharacter::FinishDeathAnim()
{
	Destroy();
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	ControllerRef = GetController<AAIController>();
	
	BlackBoardComp = ControllerRef->GetBlackboardComponent();
	BlackBoardComp->SetValueAsEnum(TEXT("CurrentState"), InitialState);
	
	GetWorld()->GetFirstPlayerController()->GetPawn<AMainCharacter>()->
	StatsComp->OnZeroHealthDelegate.AddDynamic(this, &ABossCharacter::HandlePlayerDeath);
}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

