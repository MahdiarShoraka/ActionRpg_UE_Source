// Mahdiar Shoraka All Rights Reserved


#include "Characters/BossCharacter.h"
#include "Characters/StatsComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void ABossCharacter::DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect)
{
	EEnemyState CurrentState = static_cast<EEnemyState>(BlackBoardComp->GetValueAsEnum("CurrentState"));	

	if (DetectedPawn != PawnToDetect || CurrentState != EEnemyState::Idle) return;

	BlackBoardComp->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Range);
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	BlackBoardComp = GetController<AAIController>()->GetBlackboardComponent();
	BlackBoardComp->SetValueAsEnum(TEXT("CurrentState"), InitialState);
}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

