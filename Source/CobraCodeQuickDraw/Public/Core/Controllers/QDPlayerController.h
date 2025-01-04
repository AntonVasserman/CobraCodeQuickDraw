// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Core/GameModes/QDPhase.h"
#include "Core/Utility/QDInputStatics.h"
#include "GameFramework/PlayerController.h"
#include "Subsystems/QDKeyArrow.h"
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

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext = UQDInputStatics::GetDefaultMappingContext();

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* DownAction = UQDInputStatics::GetDownInputAction();

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* LeftAction = UQDInputStatics::GetLeftInputAction();

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* RightAction = UQDInputStatics::GetRightInputAction();

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* UpAction = UQDInputStatics::GetUpInputAction();
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnPhaseChanged(EQDPhase Phase);
	virtual void OnPossess(APawn* InPawn) override;
	FORCEINLINE void RequestDownAction() { RequestActAction(EQDKeyArrow::Down); }
	FORCEINLINE void RequestLeftAction() { RequestActAction(EQDKeyArrow::Left); }
	FORCEINLINE void RequestRightAction() { RequestActAction(EQDKeyArrow::Right); }
	FORCEINLINE void RequestUpAction() { RequestActAction(EQDKeyArrow::Up); }
	void RequestActAction(EQDKeyArrow KeyArrow);

private:
	UPROPERTY()
	class AQDPlayerPawn* PossessedPlayerPawn;

	UPROPERTY()
	UUserWidget* DrawWidget = nullptr;
};
