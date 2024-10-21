// Copyright Anton Vasserman, All Rights Reserved.

#include "QDToadSamurai.h"

AQDToadSamurai::AQDToadSamurai()
{
	AttackSprite = UQuickDrawStatics::GetToadAttackSprite();
	DefeatedSprite = UQuickDrawStatics::GetToadDefeatedSprite();
	IdleSprite = UQuickDrawStatics::GetToadIdleSprite();
	CrossPaperSpriteComp->SetRelativeLocation(FVector(-20.f, 0.2f, 10.f));
	CrossPaperSpriteComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
}
