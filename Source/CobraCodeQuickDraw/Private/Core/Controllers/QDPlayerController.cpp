// Copyright Anton Vasserman, All Rights Reserved.

#include "Core/Controllers/QDPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Characters/QDPawn.h"
#include "Characters/QDPlayerPawn.h"
#include "Core/GameModes/GameStates/QDGameStateBase.h"

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
		EnhancedInputComp->BindAction(DownAction, ETriggerEvent::Started, this, &AQDPlayerController::RequestDownAction);
		EnhancedInputComp->BindAction(LeftAction, ETriggerEvent::Started, this, &AQDPlayerController::RequestLeftAction);
		EnhancedInputComp->BindAction(RightAction, ETriggerEvent::Started, this, &AQDPlayerController::RequestRightAction);
		EnhancedInputComp->BindAction(UpAction, ETriggerEvent::Started, this, &AQDPlayerController::RequestUpAction);
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

	PossessedPlayerPawn = Cast<AQDPlayerPawn>(InPawn);
}

void AQDPlayerController::RequestActAction(EQDKeyArrow KeyArrow)
{
	if (PossessedPlayerPawn->CanAct())
	{
		PossessedPlayerPawn->Act(KeyArrow);
	}
}
