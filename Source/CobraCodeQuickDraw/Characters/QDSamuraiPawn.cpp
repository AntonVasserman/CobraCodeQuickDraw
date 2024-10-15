// Fill out your copyright notice in the Description page of Project Settings.


#include "QDSamuraiPawn.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
AQDSamuraiPawn::AQDSamuraiPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Paper Sprite Component
	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	SetRootComponent(PaperSpriteComp);

	const TCHAR* TranslucentUnlitSpriteMaterialPath = TEXT("/Paper2D/TranslucentUnlitSpriteMaterial.TranslucentUnlitSpriteMaterial");
	PaperSpriteComp->SetMaterial(0, LoadObject<UMaterialInterface>(nullptr, TranslucentUnlitSpriteMaterialPath));
	const TCHAR* TanukiIdleSpritePath = TEXT("PaperSprite'/Game/QuickDraw/Characters/Tanuki/SPR_Tanuki_Idle.SPR_Tanuki_Idle'");
	PaperSpriteComp->SetSprite(LoadObject<UPaperSprite>(nullptr, TanukiIdleSpritePath));
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

