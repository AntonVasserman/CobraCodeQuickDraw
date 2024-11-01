// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDPhase.h"
#include "GameFramework/GameStateBase.h"
#include "QDGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EQDPhase, Phase);

UCLASS()
class COBRACODEQUICKDRAW_API AQDGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	FOnPhaseChanged OnPhaseChanged;
	
	FORCEINLINE EQDPhase GetPhase() const { return Phase; }

protected:
	virtual void SetPhase(EQDPhase NewPhase);

private:
	EQDPhase Phase = EQDPhase::None;

	friend class AQDGameModeBase;
};
