// Copyright Anton Vasserman, All Rights Reserved.

#include "Characters/QDEnemyPawn.h"

#include "Characters/QDPlayerPawn.h"
#include "Core/Controllers/QDAIController.h"
#include "Core/Utility/QDSpriteStatics.h"
#include "Kismet/GameplayStatics.h"

AQDEnemyPawn::AQDEnemyPawn()
{
	AttackSprite = UQDSpriteStatics::GetToadAttackSprite();
	DefeatedSprite = UQDSpriteStatics::GetToadDefeatedSprite();
	IdleSprite = UQDSpriteStatics::GetToadIdleSprite();
	CrossPaperSpriteComp->SetRelativeLocation(FVector(-20.f, 0.2f, 10.f));
	CrossPaperSpriteComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	AIControllerClass = AQDAIController::StaticClass();
}

void AQDEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	AttackTargetPawn = Cast<AQDPlayerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDPlayerPawn::StaticClass()));
	Cast<AQDPlayerPawn>(AttackTargetPawn)->OnStunned.AddDynamic(this, &AQDEnemyPawn::OnAttackTargetPawnStunned);
}

void AQDEnemyPawn::OnAttackTargetPawnStunned()
{
	Attack();
}
