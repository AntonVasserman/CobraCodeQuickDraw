// Fill out your copyright notice in the Description page of Project Settings.


#include "QDPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "CobraCodeQuickDraw/Characters/QDTanukiSamurai.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

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

	GameModeRef = Cast<AQDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeRef->OnPhaseChanged.AddDynamic(this, &AQDPlayerController::OnPhaseChanged);
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
	}
}

void AQDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedTanukiSamurai = Cast<AQDTanukiSamurai>(InPawn);
}

void AQDPlayerController::RequestAttackAction()
{
	if (PossessedTanukiSamurai->CanAttack())
	{
		PossessedTanukiSamurai->Attack();
	}
}
