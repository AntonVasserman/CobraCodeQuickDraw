// Fill out your copyright notice in the Description page of Project Settings.


#include "QDPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "CobraCodeQuickDraw/Core/Characters/QDSamuraiPawn.h"
#include "CobraCodeQuickDraw/Core/GameModes/GameStates/QDGameStateBase.h"

AQDPlayerController::AQDPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> DrawWidgetClass(TEXT("/Game/QuickDraw/UI/WBP_Draw"));
	DrawWidget = DrawWidgetClass.Succeeded() ? CreateWidget<UUserWidget>(GetWorld(), DrawWidgetClass.Class) : nullptr;
}

void AQDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	GameStateRef = GetWorld()->GetGameState<AQDGameStateBase>();
	GameStateRef->OnPhaseChanged.AddDynamic(this, &AQDPlayerController::OnPhaseChanged);
}

void AQDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
		IsValid(EnhancedInputComp))
	{
		EnhancedInputComp->BindAction(AttackAction, ETriggerEvent::Started, this, &AQDPlayerController::RequestAttackAction);
	}
}

void AQDPlayerController::OnPhaseChanged(EQDPhase Phase)
{
	switch (Phase)
	{
	case EQDPhase::Draw:
		if (IsValid(DrawWidget))
		{
			DrawWidget->AddToViewport();
		}
		break;
	case EQDPhase::Finished:
		if (IsValid(DrawWidget) && DrawWidget->IsInViewport())
		{
			DrawWidget->RemoveFromParent();
		}
		break;
	default:
		break;
	}
}

void AQDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = Cast<AQDSamuraiPawn>(InPawn);
}

void AQDPlayerController::RequestAttackAction()
{
	if (PossessedPawn->CanAttack())
	{
		PossessedPawn->Attack();
	}
}
