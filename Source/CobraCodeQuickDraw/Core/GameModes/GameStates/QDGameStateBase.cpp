// Copyright Anton Vasserman, All Rights Reserved.

#include "QDGameStateBase.h"

void AQDGameStateBase::SetPhase(EQDPhase NewPhase)
{
	Phase = NewPhase;
	OnPhaseChanged.Broadcast(Phase);
}
