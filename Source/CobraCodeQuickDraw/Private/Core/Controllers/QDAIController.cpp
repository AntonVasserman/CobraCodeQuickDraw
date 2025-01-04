// Copyright Anton Vasserman, All Rights Reserved.


#include "Core/Controllers/QDAIController.h"

#include "Characters/QDEnemyPawn.h"
#include "Characters/QDPawn.h"
#include "Core/GameModes/GameStates/QDGameStateBase.h"

void AQDAIController::BeginPlay()
{
	Super::BeginPlay();

	GameStateRef = GetWorld()->GetGameState<AQDGameStateBase>();
	GameStateRef->OnPhaseChanged.AddDynamic(this, &AQDAIController::OnPhaseChanged);
}

void AQDAIController::OnPhaseChanged(EQDPhase Phase)
{
	// We use an if instead of switch-case because otherwise we have to init TimerHandle on each call
	if (Phase == EQDPhase::Draw)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AQDAIController::RequestAttackAction, 1.f, false, DrawDelayDuration);
	}
}

void AQDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedEnemyPawn = Cast<AQDEnemyPawn>(InPawn);
}

void AQDAIController::RequestAttackAction()
{
	if (PossessedEnemyPawn->CanAttack())
	{
		PossessedEnemyPawn->Attack();
	}
}