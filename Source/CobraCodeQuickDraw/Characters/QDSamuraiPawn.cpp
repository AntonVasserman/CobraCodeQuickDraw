// Copyright Anton Vasserman, All Rights Reserved.

#include "QDSamuraiPawn.h"

#include "PaperSpriteComponent.h"
#include "CobraCodeQuickDraw/Core/Utility/UQuickDrawStatics.h"

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
}

