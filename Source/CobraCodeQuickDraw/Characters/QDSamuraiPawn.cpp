// Copyright Anton Vasserman, All Rights Reserved.

#include "QDSamuraiPawn.h"

#include "CobraCodeQuickDraw/Core/Utility/UQuickDrawStatics.h"
#include "Components/BillboardComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "PaperSpriteComponent.h"

// Sets default values
AQDSamuraiPawn::AQDSamuraiPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Paper Sprite Component
	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	SetRootComponent(PaperSpriteComp);
	
	PaperSpriteComp->SetMaterial(0, UQuickDrawStatics::GetTranslucentUnlitSpriteMaterial());
	PaperSpriteComp->SetSprite(UQuickDrawStatics::GetTanukiIdleSprite());
	PaperSpriteComp->TranslucencySortPriority = 1;

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

void AQDSamuraiPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQDSamuraiPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AQDSamuraiPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SlideInStartLocation = PaperSpriteComp->GetComponentLocation();
	SlideInEndLocation = SlideInEndBillboardComp->GetComponentLocation();

	SlideInTimelineComp->PlayFromStart();
}

void AQDSamuraiPawn::OnSlideInTimelinePostUpdate(float Alpha)
{
	FVector NewActorRelativeLocation = FMath::Lerp(SlideInStartLocation, SlideInEndLocation, Alpha);
	SetActorRelativeLocation(NewActorRelativeLocation);
}

