// Copyright Anton Vasserman, All Rights Reserved.

#include "QDToadSamurai.h"

#include "CobraCodeQuickDraw/Characters/QDTanukiSamurai.h"
#include "Kismet/GameplayStatics.h"

AQDToadSamurai::AQDToadSamurai()
{
	AttackSprite = UQuickDrawStatics::GetToadAttackSprite();
	DefeatedSprite = UQuickDrawStatics::GetToadDefeatedSprite();
	IdleSprite = UQuickDrawStatics::GetToadIdleSprite();
	CrossPaperSpriteComp->SetRelativeLocation(FVector(-20.f, 0.2f, 10.f));
	CrossPaperSpriteComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
}

void AQDToadSamurai::BeginPlay()
{
	Super::BeginPlay();

	AttackTargetPawn = Cast<AQDTanukiSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDTanukiSamurai::StaticClass()));
}
