// Copyright Anton Vasserman, All Rights Reserved.

#include "QDGameModeBase.h"

#include "CobraCodeQuickDraw/Characters/QDTanukiSamurai.h"
#include "CobraCodeQuickDraw/Enemies/QDToadSamurai.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AQDGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerTanukiSamurai = Cast<AQDTanukiSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDTanukiSamurai::StaticClass()));
	PlayerTanukiSamurai->DispatchBeginPlay();
	PlayerTanukiSamurai->OnAwaitingDuel.AddDynamic(this, &AQDGameModeBase::OnAwaitingDuel);
	PlayerTanukiSamurai->OnAttackSucceeded.AddDynamic(this, &AQDGameModeBase::OnAttackSucceeded);

	ToadSamurai = Cast<AQDToadSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDToadSamurai::StaticClass()));
	ToadSamurai->DispatchBeginPlay();
	ToadSamurai->OnAwaitingDuel.AddDynamic(this, &AQDGameModeBase::OnAwaitingDuel);
	ToadSamurai->OnAttackSucceeded.AddDynamic(this, &AQDGameModeBase::OnAttackSucceeded);

	SetPhase(EQDPhase::Intro);
}

void AQDGameModeBase::OnAttackSucceeded(const bool bPlayer)
{
	if (bPlayer)
	{
		ToadSamurai->Defeated();
	}
	else
	{
		PlayerTanukiSamurai->Defeated();
	}

	SetPhase(EQDPhase::Finished);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AQDGameModeBase::ResetDual, 1.f, false, RestartDelay);
}

void AQDGameModeBase::OnAwaitingDuel()
{
	if (IsValid(PlayerTanukiSamurai) && PlayerTanukiSamurai->IsAwaitingDuel() &&
		IsValid(ToadSamurai) && ToadSamurai->IsAwaitingDuel())
	{
		SetPhase(EQDPhase::Wait);
		const float RandomDelay = UKismetMathLibrary::RandomFloatInRange(MinDrawDelay, MaxDrawDelay);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AQDGameModeBase::OnDrawDelayFinished, 1.f, false, RandomDelay);
	}
}

void AQDGameModeBase::SetPhase(EQDPhase NewPhase)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting Phase to: %hhd"), NewPhase);
	Phase = NewPhase;
	OnPhaseChanged.Broadcast(Phase);
}

void AQDGameModeBase::OnDrawDelayFinished()
{
	SetPhase(EQDPhase::Draw);
}

void AQDGameModeBase::ResetDual()
{
	PlayerTanukiSamurai->ResetDual();
	ToadSamurai->ResetDual();
	SetPhase(EQDPhase::Intro);
}
