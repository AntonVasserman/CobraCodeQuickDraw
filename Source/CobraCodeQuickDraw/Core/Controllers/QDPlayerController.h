// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDPhase.h"
#include "CobraCodeQuickDraw/Core/Utility/QuickDrawStatics.h"
#include "GameFramework/PlayerController.h"
#include "QDPlayerController.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AQDPlayerController();

protected:
	UPROPERTY(BlueprintReadOnly)
	class AQDGameStateBase* GameStateRef = nullptr;

	UPROPERTY(VisibleAnywhere, Category=Input)
	UInputMappingContext* DefaultMappingContext = UQuickDrawStatics::GetDefaultMappingContext();

	UPROPERTY(VisibleAnywhere, Category=Input)
	UInputAction* AttackAction = UQuickDrawStatics::GetAttackInputAction();
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnPhaseChanged(EQDPhase Phase);
	virtual void OnPossess(APawn* InPawn) override;
	void RequestAttackAction();

private:
	UPROPERTY()
	class AQDSamuraiPawn* PossessedPawn;

	UPROPERTY()
	UUserWidget* DrawWidget = nullptr;
};
