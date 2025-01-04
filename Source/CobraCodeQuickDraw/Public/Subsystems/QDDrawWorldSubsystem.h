// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QDKeyArrow.h"
#include "Core/GameModes/QDPhase.h"
#include "Subsystems/WorldSubsystem.h"
#include "QDDrawWorldSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDrawComboFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDrawComboSucceeded);

UCLASS()
class COBRACODEQUICKDRAW_API UQDDrawWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	FOnDrawComboFailed OnDrawComboFailed;
	FOnDrawComboSucceeded OnDrawComboSucceeded;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void AddKeyArrowToCombo(EQDKeyArrow KeyArrow);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AQDGameStateBase* GameStateRef = nullptr;
	
	bool bAcceptingInput = false;
	int Current = 0;
	TArray<EQDKeyArrow> CurrentKeyArrows;

	UFUNCTION()
	void OnPhaseChanged(EQDPhase Phase);
	
	void DrawKeyArrows(int Count);

	void GenerateKeyArrows(int Count);
};
