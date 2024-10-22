// Copyright Anton Vasserman, All Rights Reserved.

#include "QDGameModeBase.h"

#include "CobraCodeQuickDraw/Characters/QDExclamationMark.h"
#include "CobraCodeQuickDraw/Characters/QDTanukiSamurai.h"
#include "CobraCodeQuickDraw/Enemies/QDToadSamurai.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AQDGameModeBase::AQDGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AQDGameModeBase::AttackedSuccessfully(const bool bPlayer) const
{
	ExclamationMark->SetVisibility(false);
	
	if (bPlayer)
	{
		ToadSamurai->Defeated();
	}
	else
	{
		PlayerTanukiSamurai->Defeated();
	}
}

void AQDGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ElapsedTime += DeltaSeconds;

	if (Phase != EQDPhase::Intro)
	{
		return;
	}

	if (ElapsedTime > RoundStartTime)
	{
		Phase = EQDPhase::Wait;
		const float RandomDelay = UKismetMathLibrary::RandomFloatInRange(MinDrawDelay, MaxDrawDelay);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AQDGameModeBase::OnDrawDelayFinished, 1.f, false, RandomDelay);
	}
}

void AQDGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ExclamationMark = Cast<AQDExclamationMark>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDExclamationMark::StaticClass()));
	PlayerTanukiSamurai = Cast<AQDTanukiSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDTanukiSamurai::StaticClass()));
	ToadSamurai = Cast<AQDToadSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDToadSamurai::StaticClass()));
}

void AQDGameModeBase::OnDrawDelayFinished()
{
	Phase = EQDPhase::Draw;
	ExclamationMark->SetVisibility(true);
}
