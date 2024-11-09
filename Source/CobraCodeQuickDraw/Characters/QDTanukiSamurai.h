// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CobraCodeQuickDraw/Core/Characters/QDSamuraiPawn.h"
#include "QDTanukiSamurai.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDTanukiSamurai : public AQDSamuraiPawn
{
	GENERATED_BODY()

public:
	AQDTanukiSamurai();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* CameraComp;

	virtual void BeginPlay() override;
	virtual void OnPhaseChanged(EQDPhase Phase) override;
};
