// Fill out your copyright notice in the Description page of Project Settings.


#include "QDExclamationMark.h"

#include "PaperSprite.h"
#include "CobraCodeQuickDraw/Core/Utility/QuickDrawStatics.h"

AQDExclamationMark::AQDExclamationMark()
{
	PrimaryActorTick.bCanEverTick = true;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = SpriteComp;
	SpriteComp->SetMaterial(0, UQuickDrawStatics::GetTranslucentUnlitSpriteMaterial());
	SpriteComp->SetSprite(Cast<UPaperSprite>(UQuickDrawStatics::GetExclamationMarkSprite()));
	SpriteComp->TranslucencySortPriority = 1;
}

void AQDExclamationMark::BeginPlay()
{
	Super::BeginPlay();
	
	SetVisibility(false);
}

