// Copyright Anton Vasserman, All Rights Reserved.

#include "QDTanukiSamurai.h"

#include "PaperSpriteComponent.h"

AQDTanukiSamurai::AQDTanukiSamurai()
{
	AttackSprite = UQuickDrawStatics::GetTanukiAttackSprite();
	DefeatedSprite = UQuickDrawStatics::GetTanukiDefeatedSprite();
	IdleSprite = UQuickDrawStatics::GetTanukiIdleSprite();
	CrossPaperSpriteComp->SetRelativeLocation(FVector(30.f, 0.2f, 10.f));
}
