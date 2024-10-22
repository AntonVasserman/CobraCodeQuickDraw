// Copyright Anton Vasserman, All Rights Reserved.

#include "QDToadSamurai.h"

AQDToadSamurai::AQDToadSamurai()
{
	AttackSprite = UQuickDrawStatics::GetToadAttackSprite();
	DefeatedSprite = UQuickDrawStatics::GetToadDefeatedSprite();
	IdleSprite = UQuickDrawStatics::GetToadIdleSprite();
	CrossPaperSpriteComp->SetRelativeLocation(FVector(-20.f, 0.2f, 10.f));
	CrossPaperSpriteComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
}

void AQDToadSamurai::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef->OnDrawPhaseStarted.AddDynamic(this, &AQDToadSamurai::OnDrawPhaseStarted);
}

void AQDToadSamurai::OnDrawDelayFinished()
{
	Attack();
}

void AQDToadSamurai::OnDrawPhaseStarted()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AQDToadSamurai::OnDrawDelayFinished, 1.f, false, DrawDelayDuration);
}
