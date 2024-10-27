// Copyright Anton Vasserman, All Rights Reserved.

#include "QDTanukiSamurai.h"

#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "CobraCodeQuickDraw/Enemies/QDToadSamurai.h"
#include "Kismet/GameplayStatics.h"

AQDTanukiSamurai::AQDTanukiSamurai()
{
	AttackSprite = UQuickDrawStatics::GetTanukiAttackSprite();
	DefeatedSprite = UQuickDrawStatics::GetTanukiDefeatedSprite();
	IdleSprite = UQuickDrawStatics::GetTanukiIdleSprite();
	PaperSpriteComp->TranslucencySortPriority = 1; // TODO: Consider changing this to use somehow the 'Z' as we want the toad to be behind the Tanuki
	CrossPaperSpriteComp->SetRelativeLocation(FVector(30.f, 0.2f, 10.f));

	// Setup Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(PaperSpriteComp);
	CameraComp->SetUsingAbsoluteLocation(true);
	CameraComp->SetWorldLocation(FVector(0.f, 275.f, 0.f));
	CameraComp->SetUsingAbsoluteRotation(true);
	CameraComp->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
	CameraComp->PostProcessSettings.bOverride_AutoExposureMethod = true;
	CameraComp->PostProcessSettings.AutoExposureMethod = AEM_Manual;
	CameraComp->PostProcessSettings.bOverride_AutoExposureBias = true;
	CameraComp->PostProcessSettings.AutoExposureBias = 10.2f;
}

void AQDTanukiSamurai::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
	AttackTargetPawn = Cast<AQDToadSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDToadSamurai::StaticClass()));
}
