// Copyright Anton Vasserman, All Rights Reserved.

#include "Core/GameModes/GameStates/QDGameStateBase.h"
#include "Core/GameModes/QDPhase.h"

void AQDGameStateBase::SetPhase(EQDPhase NewPhase)
{
	Phase = NewPhase;
	OnPhaseChanged.Broadcast(Phase);
}
