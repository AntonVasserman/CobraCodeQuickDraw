// Copyright Anton Vasserman, All Rights Reserved.

#include "Characters/QDPawn.h"

#include "PaperSpriteComponent.h"
#include "Components/TimelineComponent.h"
#include "Core/GameModes/QDPhase.h"
#include "Core/GameModes/GameStates/QDGameStateBase.h"
#include "Core/Utility/QDSpriteStatics.h"
#include "Core/Utility/QDStatics.h"
#include "Curves/CurveFloat.h"

AQDPawn::AQDPawn()
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
	SlideInTimelineUpdateDelegate.BindDynamic(this, &AQDPawn::OnSlideInTimelineUpdate);
	SlideInTimelineFinishedDelegate.BindDynamic(this, &AQDPawn::OnSlideInTimelineFinished);
	SlideInTimelineComp->SetPlayRate(SlideInPlayRate);

	// Setup Attack Anim Timeline
	AttackTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("Attack Animation Timeline"));
	AttackUpdateDelegate.BindDynamic(this, &AQDPawn::OnAttackTimelineUpdate);
	AttackEventDelegate.BindDynamic(this, &AQDPawn::OnAttackTimelineEvent);
	AttackTimelineComp->SetPlayRate(AttackPlayRate);
}

void AQDPawn::Attack()
{
	bCanAttack = false;
	AttackTimelineComp->PlayFromStart();
}

void AQDPawn::Defeated()
{
	SetCrossVisibility(false);
	PaperSpriteComp->SetSprite(DefeatedSprite);
	OnDefeated.Broadcast();
}

void AQDPawn::BeginPlay()
{
	Super::BeginPlay();

	// Setup GameState reference
	GameStateRef = GetWorld()->GetGameState<AQDGameStateBase>();
	GameStateRef->OnPhaseChanged.AddDynamic(this, &AQDPawn::OnPhaseChanged);

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

void AQDPawn::OnPhaseChanged(EQDPhase Phase)
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

void AQDPawn::OnSlideInTimelineFinished()
{
	bAwaitingDuel = true;
	OnAwaitingDuel.Broadcast();
}

void AQDPawn::OnSlideInTimelineUpdate(float Alpha)
{
	SetActorRelativeLocation(FMath::Lerp(SlideInStartLocation, SlideInEndLocation, Alpha));
}

void AQDPawn::OnAttackTimelineUpdate(float Alpha)
{
	SetActorRelativeLocation(FMath::Lerp(SlideInEndLocation, AttackEndLocation, Alpha));
}

void AQDPawn::OnAttackTimelineEvent()
{
	PaperSpriteComp->SetSprite(AttackSprite);
	AttackTargetPawn->Defeated();
}

void AQDPawn::PostInitProperties()
{
	Super::PostInitProperties();
	PaperSpriteComp->SetSprite(IdleSprite);
}

void AQDPawn::ResetDuel()
{
	PaperSpriteComp->SetSprite(IdleSprite);
	bAwaitingDuel = false;
	bCanAttack = false;
}

