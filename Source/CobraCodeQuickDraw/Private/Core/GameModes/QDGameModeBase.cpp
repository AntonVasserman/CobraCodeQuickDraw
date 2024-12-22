// Copyright Anton Vasserman, All Rights Reserved.

#include "Core/GameModes/QDGameModeBase.h"

#include "Characters/QDTanukiSamurai.h"
#include "Core/Controllers/QDPlayerController.h"
#include "Core/GameModes/GameStates/QDGameStateBase.h"
#include "Enemies/QDToadSamurai.h"
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

	PlayerTanukiSamurai = Cast<AQDTanukiSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDTanukiSamurai::StaticClass()));
	PlayerTanukiSamurai->DispatchBeginPlay();
	PlayerTanukiSamurai->OnAwaitingDuel.AddDynamic(this, &AQDGameModeBase::OnAwaitingDuel);
	PlayerTanukiSamurai->OnDefeated.AddDynamic(this, &AQDGameModeBase::OnDefeated);
	PlayerTanukiSamurai->OnStunned.AddDynamic(this, &AQDGameModeBase::OnStunned);

	ToadSamurai = Cast<AQDToadSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDToadSamurai::StaticClass()));
	ToadSamurai->DispatchBeginPlay();
	ToadSamurai->OnAwaitingDuel.AddDynamic(this, &AQDGameModeBase::OnAwaitingDuel);
	ToadSamurai->OnDefeated.AddDynamic(this, &AQDGameModeBase::OnDefeated);

	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Intro);
}

void AQDGameModeBase::OnDefeated()
{
	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Finished);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AQDGameModeBase::ResetDual, 1.f, false, RestartDelay);
}

void AQDGameModeBase::OnStunned()
{
	GetWorldTimerManager().ClearTimer(DrawDelayTimerHandle);
	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::PlayerStunned);
}

void AQDGameModeBase::OnAwaitingDuel()
{
	if (IsValid(PlayerTanukiSamurai) && PlayerTanukiSamurai->IsAwaitingDuel() &&
		IsValid(ToadSamurai) && ToadSamurai->IsAwaitingDuel())
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
	PlayerTanukiSamurai->ResetDual();
	ToadSamurai->ResetDual();
	Cast<AQDGameStateBase>(GameState)->SetPhase(EQDPhase::Intro);
}
