// Copyright Anton Vasserman, All Rights Reserved.

#include "Core/GameModes/QDGameModeBase.h"

#include "Characters/QDEnemyPawn.h"
#include "Characters/QDPlayerPawn.h"
#include "Core/Controllers/QDPlayerController.h"
#include "Core/GameModes/GameStates/QDGameStateBase.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AQDGameModeBase::AQDGameModeBase()
{
	GameStateClass = AQDGameStateBase::StaticClass();
	PlayerControllerClass = AQDPlayerController::StaticClass();
}

void AQDGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<AQDPlayerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDPlayerPawn::StaticClass()));
	PlayerPawn->DispatchBeginPlay();
	PlayerPawn->OnAwaitingDuel.AddDynamic(this, &AQDGameModeBase::OnAwaitingDuel);
	PlayerPawn->OnDefeated.AddDynamic(this, &AQDGameModeBase::OnDefeated);

	EnemyPawn = Cast<AQDEnemyPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDEnemyPawn::StaticClass()));
	EnemyPawn->DispatchBeginPlay();
	EnemyPawn->OnAwaitingDuel.AddDynamic(this, &AQDGameModeBase::OnAwaitingDuel);
	EnemyPawn->OnDefeated.AddDynamic(this, &AQDGameModeBase::OnDefeated);

	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Intro);
}

void AQDGameModeBase::OnDefeated()
{
	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Finished);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AQDGameModeBase::ResetDual, 1.f, false, RestartDelay);
}

void AQDGameModeBase::OnAwaitingDuel()
{
	if (IsValid(PlayerPawn) && PlayerPawn->IsAwaitingDuel() &&
		IsValid(EnemyPawn) && EnemyPawn->IsAwaitingDuel())
	{
		Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Wait);
		const float RandomDelay = UKismetMathLibrary::RandomFloatInRange(MinDrawDelay, MaxDrawDelay);
		GetWorldTimerManager().SetTimer(DrawDelayTimerHandle, this, &AQDGameModeBase::OnDrawDelayFinished, 1.f, false, RandomDelay);
	}
}

void AQDGameModeBase::OnDrawDelayFinished()
{
	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Draw);
}

void AQDGameModeBase::ResetDual()
{
	PlayerPawn->ResetDuel();
	EnemyPawn->ResetDuel();
	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Intro);
}
