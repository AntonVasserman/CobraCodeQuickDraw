// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QDPhase.h"
#include "GameFramework/GameModeBase.h"
#include "QDGameModeBase.generated.h"

class AQDToadSamurai;
class AQDTanukiSamurai;
class AQDExclamationMark;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EQDPhase, Phase);

UCLASS()
class COBRACODEQUICKDRAW_API AQDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	FOnPhaseChanged OnPhaseChanged;

	FORCEINLINE EQDPhase GetPhase() const { return Phase; }

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnAttackSucceeded(const bool bPlayer);
	UFUNCTION()
	void OnAwaitingDuel();
	virtual void SetPhase(EQDPhase NewPhase);

private:
	EQDPhase Phase = EQDPhase::None;
	
	UPROPERTY()
	AQDExclamationMark* ExclamationMark;

	UPROPERTY()
	AQDTanukiSamurai* PlayerTanukiSamurai = nullptr;

	UPROPERTY()
	AQDToadSamurai* ToadSamurai = nullptr;
	
	float MinDrawDelay = 1.f;
	float MaxDrawDelay = 3.f;
	float RestartDelay = 2.f;

	void OnDrawDelayFinished();
	void ResetDual();
};
