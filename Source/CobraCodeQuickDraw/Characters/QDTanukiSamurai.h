// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CobraCodeQuickDraw/Core/Characters/QDSamuraiPawn.h"
#include "QDTanukiSamurai.generated.h"

class UCameraComponent;

UCLASS()
class COBRACODEQUICKDRAW_API AQDTanukiSamurai : public AQDSamuraiPawn
{
	GENERATED_BODY()

public:
	AQDTanukiSamurai();

protected:
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	virtual void BeginPlay() override;
	virtual void OnPhaseChanged(EQDPhase Phase) override;
};
