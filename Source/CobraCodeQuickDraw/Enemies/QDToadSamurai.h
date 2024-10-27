// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CobraCodeQuickDraw/Core/Characters/QDSamuraiPawn.h"
#include "QDToadSamurai.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDToadSamurai : public AQDSamuraiPawn
{
	GENERATED_BODY()

public:
	AQDToadSamurai();

protected:
	virtual void BeginPlay() override;
	virtual void OnPhaseChanged(EQDPhase Phase) override;

private:
	float DrawDelayDuration = 2.f;
};
