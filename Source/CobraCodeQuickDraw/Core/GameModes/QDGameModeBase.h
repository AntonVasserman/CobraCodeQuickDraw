// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QDPhase.h"
#include "GameFramework/GameModeBase.h"
#include "QDGameModeBase.generated.h"

class AQDToadSamurai;
class AQDTanukiSamurai;
class AQDExclamationMark;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawPhaseStarted);

UCLASS()
class COBRACODEQUICKDRAW_API AQDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	FDrawPhaseStarted OnDrawPhaseStarted;

	AQDGameModeBase();
	
	void AttackedSuccessfully(const bool bPlayer);
	FORCEINLINE EQDPhase GetPhase() const { return Phase; }
	FORCEINLINE void SetGameFinished() { Phase = EQDPhase::Finished; }
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadWrite)
	EQDPhase Phase = EQDPhase::Intro;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AQDExclamationMark* ExclamationMark;

	UPROPERTY()
	AQDTanukiSamurai* PlayerTanukiSamurai;

	UPROPERTY()
	AQDToadSamurai* ToadSamurai;

	float ElapsedTime = 0.f;
	float RoundStartTime = 0.f;
	float MinDrawDelay = 1.f;
	float MaxDrawDelay = 3.f;
	float RestartDelay = 2.f;

	void OnDrawDelayFinished();
	void ResetDual();
};
