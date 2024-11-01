// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QDGameModeBase.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AQDGameModeBase();
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnAwaitingDuel();
	UFUNCTION()
	void OnDefeated();
	UFUNCTION()
	void OnStunned();

private:
	FTimerHandle DrawDelayTimerHandle;
	
	UPROPERTY()
	class AQDTanukiSamurai* PlayerTanukiSamurai = nullptr;

	UPROPERTY()
	class AQDToadSamurai* ToadSamurai = nullptr;
	
	float MinDrawDelay = 1.f;
	float MaxDrawDelay = 3.f;
	float RestartDelay = 2.f;

	void OnDrawDelayFinished();
	void ResetDual();
};
