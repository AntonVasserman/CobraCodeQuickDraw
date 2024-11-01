// Copyright Anton Vasserman, All Rights Reserved.

#include "QDGameStateBase.h"

void AQDGameStateBase::SetPhase(EQDPhase NewPhase)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting Phase to: %hhd"), NewPhase);
	Phase = NewPhase;
	OnPhaseChanged.Broadcast(Phase);
}
