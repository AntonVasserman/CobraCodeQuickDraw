// Copyright Anton Vasserman, All Rights Reserved.

#include "QDSamuraiPawn.h"

#include "CobraCodeQuickDraw/Core/Utility/QuickDrawStatics.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "PaperSpriteComponent.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDGameModeBase.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDPhase.h"
#include "Kismet/GameplayStatics.h"

AQDSamuraiPawn::AQDSamuraiPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Paper Sprite Component
	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	SetRootComponent(PaperSpriteComp);
	
	PaperSpriteComp->SetMaterial(0, UQuickDrawStatics::GetTranslucentUnlitSpriteMaterial());
	PaperSpriteComp->SetSprite(IdleSprite);
	PaperSpriteComp->TranslucencySortPriority = 1;

	// Setup Cross Paper Sprite Component
	CrossPaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Cross Paper Sprite"));
	CrossPaperSpriteComp->SetupAttachment(PaperSpriteComp);
	CrossPaperSpriteComp->SetMaterial(0, UQuickDrawStatics::GetTranslucentUnlitSpriteMaterial());
	CrossPaperSpriteComp->SetSprite(Cast<UPaperSprite>(UQuickDrawStatics::GetCrossSprite()));
	CrossPaperSpriteComp->TranslucencySortPriority = 2;
	
	// Setup Slide In Animation Timeline
	SlideInTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("Slide In Animation Timeline"));
	SlideInTimelineUpdateDelegate.BindDynamic(this, &AQDSamuraiPawn::OnSlideInTimelineUpdate);
	SlideInTimelineComp->AddInterpFloat(SlideInCurveFloat, SlideInTimelineUpdateDelegate);
	SlideInTimelineFinishedDelegate.BindDynamic(this, &AQDSamuraiPawn::OnSlideInTimelineFinished);
	SlideInTimelineComp->SetTimelineFinishedFunc(SlideInTimelineFinishedDelegate);
	SlideInTimelineComp->SetPlayRate(SlideInPlayRate);

	// Setup Attack Anim Timeline
	AttackTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("Attack Animation Timeline"));
	AttackUpdateDelegate.BindDynamic(this, &AQDSamuraiPawn::OnAttackTimelineUpdate);
	AttackTimelineComp->AddInterpFloat(AttackCurveFloat, AttackUpdateDelegate);
	AttackEventDelegate.BindDynamic(this, &AQDSamuraiPawn::OnAttackTimelineEvent);
	AttackTimelineComp->AddEvent(0.6f, AttackEventDelegate);
	AttackTimelineComp->SetPlayRate(AttackPlayRate);
}

void AQDSamuraiPawn::Attack()
{
	switch (GameModeRef->GetPhase())
	{
	case EQDPhase::Wait:
		SetCrossVisibility(true);
		bCanAttack = false;
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
	PaperSpriteComp->SetSprite(DefeatedSprite);
	SetCrossVisibility(false);
}

void AQDSamuraiPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeRef = Cast<AQDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeRef->OnPhaseChanged.AddDynamic(this, &AQDSamuraiPawn::OnPhaseChanged);

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
	OnAttackSucceeded.Broadcast(IsPlayerControlled());
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

