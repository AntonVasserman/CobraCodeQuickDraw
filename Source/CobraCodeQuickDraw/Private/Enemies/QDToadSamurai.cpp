// Copyright Anton Vasserman, All Rights Reserved.

#include "Enemies/QDToadSamurai.h"

#include "Characters/QDTanukiSamurai.h"
#include "Core/Controllers/QDAIController.h"
#include "Core/GameModes/GameStates/QDGameStateBase.h"
#include "Core/Utility/QDSpriteStatics.h"
#include "Kismet/GameplayStatics.h"

AQDToadSamurai::AQDToadSamurai()
{
	AttackSprite = UQDSpriteStatics::GetToadAttackSprite();
	DefeatedSprite = UQDSpriteStatics::GetToadDefeatedSprite();
	IdleSprite = UQDSpriteStatics::GetToadIdleSprite();
	CrossPaperSpriteComp->SetRelativeLocation(FVector(-20.f, 0.2f, 10.f));
	CrossPaperSpriteComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	AIControllerClass = AQDAIController::StaticClass();
}

void AQDToadSamurai::Attack()
{
	Super::Attack();

	switch (GameStateRef->GetPhase())
	{
	case EQDPhase::PlayerStunned:
		bCanAttack = false;
		AttackTimelineComp->PlayFromStart();
		break;
	default:
		break;
	}
}

void AQDToadSamurai::BeginPlay()
{
	Super::BeginPlay();

	AttackTargetPawn = Cast<AQDTanukiSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDTanukiSamurai::StaticClass()));
}

void AQDToadSamurai::OnPhaseChanged(EQDPhase Phase)
{
	Super::OnPhaseChanged(Phase);

	switch (Phase)
	{
	case EQDPhase::PlayerStunned:
		Attack();
		break;
	default:
		break;
	}
}
