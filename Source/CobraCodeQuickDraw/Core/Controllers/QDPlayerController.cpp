// Fill out your copyright notice in the Description page of Project Settings.


#include "QDPlayerController.h"

#include "CobraCodeQuickDraw/Characters/QDTanukiSamurai.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AQDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}
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
