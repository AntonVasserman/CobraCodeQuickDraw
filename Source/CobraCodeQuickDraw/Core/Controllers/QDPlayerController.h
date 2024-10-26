// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDPhase.h"
#include "QDPlayerController.generated.h"

class AQDGameModeBase;
class AQDTanukiSamurai;

UCLASS()
class COBRACODEQUICKDRAW_API AQDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AQDPlayerController();

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* AttackAction = nullptr;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnPhaseChanged(EQDPhase Phase);
	virtual void OnPossess(APawn* InPawn) override;
	void RequestAttackAction();

private:
	UPROPERTY()
	AQDGameModeBase* GameModeRef = nullptr;
	
	UPROPERTY()
	AQDTanukiSamurai* PossessedTanukiSamurai;

	UPROPERTY()
	UUserWidget* DrawWidget = nullptr;
};