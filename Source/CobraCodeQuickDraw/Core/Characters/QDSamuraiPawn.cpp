// Copyright Anton Vasserman, All Rights Reserved.

#include "QDSamuraiPawn.h"

#include "CobraCodeQuickDraw/Core/Utility/QuickDrawStatics.h"
#include "Components/BillboardComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "PaperSpriteComponent.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AQDSamuraiPawn::AQDSamuraiPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Paper Sprite Component
	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	SetRootComponent(PaperSpriteComp);
	
	PaperSpriteComp->SetMaterial(0, UQuickDrawStatics::GetTranslucentUnlitSpriteMaterial());
	PaperSpriteComp->TranslucencySortPriority = 1;

	// Setup Cross Paper Sprite Component
	CrossPaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Cross Paper Sprite"));
	CrossPaperSpriteComp->SetupAttachment(PaperSpriteComp);
	CrossPaperSpriteComp->SetMaterial(0, UQuickDrawStatics::GetTranslucentUnlitSpriteMaterial());
	CrossPaperSpriteComp->SetSprite(Cast<UPaperSprite>(UQuickDrawStatics::GetCrossSprite()));
	CrossPaperSpriteComp->TranslucencySortPriority = 2;
	
	// Setup Billboard for Slide In Animation
	SlideInEndBillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("Slide In Animation End Billboard"));
	SlideInEndBillboardComp->SetSprite(Cast<UTexture2D>(UQuickDrawStatics::GetTargetPointTexture()));
	SlideInEndBillboardComp->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	SlideInTimelinePostUpdateDelegate.BindDynamic(this, &AQDSamuraiPawn::OnSlideInTimelinePostUpdate);
	
	// Setup Slide In Animation Timeline
	SlideInTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("Slide In Animation Timeline"));
	SlideInTimelineComp->AddInterpFloat(SlideInCurveFloat, SlideInTimelinePostUpdateDelegate);
	SlideInTimelineComp->SetFloatCurve(SlideInCurveFloat, TEXT("Alpha"));
	SlideInTimelineComp->SetPlayRate(SlideInPlayRate);
}

void AQDSamuraiPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	PaperSpriteComp->SetSprite(IdleSprite);
}

void AQDSamuraiPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQDSamuraiPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
		PaperSpriteComp->SetSprite(AttackSprite);
		break;
	default:
		break;
	}
}

void AQDSamuraiPawn::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<AQDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	SlideInStartLocation = PaperSpriteComp->GetComponentLocation();
	SlideInEndLocation = SlideInEndBillboardComp->GetComponentLocation();

	SlideInTimelineComp->PlayFromStart();
	SetCrossVisibility(false);
}

void AQDSamuraiPawn::OnSlideInTimelinePostUpdate(float Alpha)
{
	SetActorRelativeLocation(FMath::Lerp(SlideInStartLocation, SlideInEndLocation, Alpha));
}

