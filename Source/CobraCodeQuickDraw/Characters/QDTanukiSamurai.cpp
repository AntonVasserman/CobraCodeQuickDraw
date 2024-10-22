// Copyright Anton Vasserman, All Rights Reserved.

#include "QDTanukiSamurai.h"

#include "PaperSpriteComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

AQDTanukiSamurai::AQDTanukiSamurai()
{
	AttackSprite = UQuickDrawStatics::GetTanukiAttackSprite();
	DefeatedSprite = UQuickDrawStatics::GetTanukiDefeatedSprite();
	IdleSprite = UQuickDrawStatics::GetTanukiIdleSprite();
	PaperSpriteComp->TranslucencySortPriority = 1; // TODO: Consider changing this to use somehow the 'Z' as we want the toad to be behind the Tanuki
	CrossPaperSpriteComp->SetRelativeLocation(FVector(30.f, 0.2f, 10.f));
}

void AQDTanukiSamurai::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
	ACameraActor* Camera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	Cast<APlayerController>(GetController())->SetViewTargetWithBlend(Camera);
}
