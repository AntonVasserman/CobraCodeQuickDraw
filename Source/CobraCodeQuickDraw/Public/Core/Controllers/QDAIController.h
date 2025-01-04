// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Core/GameModes/QDPhase.h"
#include "QDAIController.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	class AQDGameStateBase* GameStateRef = nullptr;
	
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnPhaseChanged(EQDPhase Phase);
	virtual void OnPossess(APawn* InPawn) override;
	void RequestAttackAction();

private:
	UPROPERTY()
	class AQDEnemyPawn* PossessedEnemyPawn;

	float DrawDelayDuration = 3.f;
};
