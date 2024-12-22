// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/QDSamuraiPawn.h"
#include "QDToadSamurai.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDToadSamurai : public AQDSamuraiPawn
{
	GENERATED_BODY()

public:
	AQDToadSamurai();

	virtual void Attack() override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPhaseChanged(EQDPhase Phase) override;
};
