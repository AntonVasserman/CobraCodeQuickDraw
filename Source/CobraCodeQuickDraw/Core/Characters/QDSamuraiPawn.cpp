// Copyright Anton Vasserman, All Rights Reserved.

#include "QDSamuraiPawn.h"

#include "PaperSpriteComponent.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDPhase.h"
#include "CobraCodeQuickDraw/Core/GameModes/GameStates/QDGameStateBase.h"
#include "CobraCodeQuickDraw/Core/Utility/QDSpriteStatics.h"
#include "CobraCodeQuickDraw/Core/Utility/QDStatics.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"

AQDSamuraiPawn::AQDSamuraiPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Paper Sprite Component
	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	SetRootComponent(PaperSpriteComp);
	
	PaperSpriteComp->SetMaterial(0, UQDStatics::GetTranslucentUnlitSpriteMaterial());
	PaperSpriteComp->SetSprite(IdleSprite);
	PaperSpriteComp->TranslucencySortPriority = 1;

	// Setup Cross Paper Sprite Component
	CrossPaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Cross Paper Sprite"));
	CrossPaperSpriteComp->SetupAttachment(PaperSpriteComp);
	CrossPaperSpriteComp->SetMaterial(0, UQDStatics::GetTranslucentUnlitSpriteMaterial());
	CrossPaperSpriteComp->SetSprite(Cast<UPaperSprite>(UQDSpriteStatics::GetCrossSprite()));
	CrossPaperSpriteComp->TranslucencySortPriority = 2;
	
	// Setup Slide In Animation Timeline
	SlideInTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("Slide In Animation Timeline"));
	SlideInTimelineUpdateDelegate.BindDynamic(this, &AQDSamuraiPawn::OnSlideInTimelineUpdate);
	SlideInTimelineFinishedDelegate.BindDynamic(this, &AQDSamuraiPawn::OnSlideInTimelineFinished);
	SlideInTimelineComp->SetPlayRate(SlideInPlayRate);

	// Setup Attack Anim Timeline
	AttackTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("Attack Animation Timeline"));
	AttackUpdateDelegate.BindDynamic(this, &AQDSamuraiPawn::OnAttackTimelineUpdate);
	AttackEventDelegate.BindDynamic(this, &AQDSamuraiPawn::OnAttackTimelineEvent);
	AttackTimelineComp->SetPlayRate(AttackPlayRate);
}

void AQDSamuraiPawn::Attack()
{
	switch (GameStateRef->GetPhase())
	{
	case EQDPhase::Wait:
		OnStunned.Broadcast();
		break;
	case EQDPhase::Draw:
		bCanAttack = false;
		AttackTimelineComp->PlayFromStart();
		break;
	default:
		break;
	}
}

void AQDSamuraiPawn::Defeated()
{
	SetCrossVisibility(false);
	PaperSpriteComp->SetSprite(DefeatedSprite);
	OnDefeated.Broadcast();
}

void AQDSamuraiPawn::BeginPlay()
{
	Super::BeginPlay();

	// Setup GameState reference
	GameStateRef = GetWorld()->GetGameState<AQDGameStateBase>();
	GameStateRef->OnPhaseChanged.AddDynamic(this, &AQDSamuraiPawn::OnPhaseChanged);

	// Setup Bindings
	SlideInTimelineComp->AddInterpFloat(SlideInCurveFloat, SlideInTimelineUpdateDelegate);
	SlideInTimelineComp->SetTimelineFinishedFunc(SlideInTimelineFinishedDelegate);
	AttackTimelineComp->AddInterpFloat(AttackCurveFloat, AttackUpdateDelegate);
	AttackTimelineComp->AddEvent(0.6f, AttackEventDelegate);
	
	PaperSpriteComp->SetSprite(IdleSprite);
	
	SlideInStartLocation = PaperSpriteComp->GetComponentLocation();
	SlideInEndLocation = FMath::Lerp(SlideInStartLocation, FVector::ZeroVector, SlideInAlphaFromCenter);

	SetCrossVisibility(false);
}

void AQDSamuraiPawn::OnPhaseChanged(EQDPhase Phase)
{
	switch (Phase)
	{
	case EQDPhase::Intro:
		SlideInTimelineComp->PlayFromStart();
		break;
	case EQDPhase::Wait:
		AttackEndLocation = FMath::Lerp(GetActorLocation(), AttackTargetPawn->GetActorLocation(), AttackAlphaFromTarget);
		bCanAttack = true;
		break;
	default:
		break;
	}
}

void AQDSamuraiPawn::OnSlideInTimelineFinished()
{
	bAwaitingDuel = true;
	OnAwaitingDuel.Broadcast();
}

void AQDSamuraiPawn::OnSlideInTimelineUpdate(float Alpha)
{
	SetActorRelativeLocation(FMath::Lerp(SlideInStartLocation, SlideInEndLocation, Alpha));
}

void AQDSamuraiPawn::OnAttackTimelineUpdate(float Alpha)
{
	SetActorRelativeLocation(FMath::Lerp(SlideInEndLocation, AttackEndLocation, Alpha));
}

void AQDSamuraiPawn::OnAttackTimelineEvent()
{
	PaperSpriteComp->SetSprite(AttackSprite);
	AttackTargetPawn->Defeated();
}

void AQDSamuraiPawn::PostInitProperties()
{
	Super::PostInitProperties();
	PaperSpriteComp->SetSprite(IdleSprite);
}

void AQDSamuraiPawn::ResetDual()
{
	PaperSpriteComp->SetSprite(IdleSprite);
	bAwaitingDuel = false;
	bCanAttack = false;
}

