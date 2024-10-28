// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDPhase.h"

#include "QDAIController.generated.h"

class AQDSamuraiPawn;
class AQDGameModeBase;

UCLASS()
class COBRACODEQUICKDRAW_API AQDAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnPhaseChanged(EQDPhase Phase);
	virtual void OnPossess(APawn* InPawn) override;
	void RequestAttackAction();

private:
	UPROPERTY()
	AQDGameModeBase* GameModeRef = nullptr;
	
	UPROPERTY()
	AQDSamuraiPawn* PossessedPawn;

	float DrawDelayDuration = 2.f;
};
