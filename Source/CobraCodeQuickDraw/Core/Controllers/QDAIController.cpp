// Fill out your copyright notice in the Description page of Project Settings.


#include "QDAIController.h"

#include "CobraCodeQuickDraw/Core/Characters/QDSamuraiPawn.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AQDAIController::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<AQDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeRef->OnPhaseChanged.AddDynamic(this, &AQDAIController::OnPhaseChanged);
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

	PossessedPawn = Cast<AQDSamuraiPawn>(InPawn);
}

void AQDAIController::RequestAttackAction()
{
	if (PossessedPawn->CanAttack())
	{
		PossessedPawn->Attack();
	}
}