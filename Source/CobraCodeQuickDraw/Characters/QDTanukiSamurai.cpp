// Copyright Anton Vasserman, All Rights Reserved.

#include "QDTanukiSamurai.h"

#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "CobraCodeQuickDraw/Enemies/QDToadSamurai.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AQDTanukiSamurai::AQDTanukiSamurai()
{
	AttackSprite = UQDStatics::GetTanukiAttackSprite();
	DefeatedSprite = UQDStatics::GetTanukiDefeatedSprite();
	IdleSprite = UQDStatics::GetTanukiIdleSprite();
	PaperSpriteComp->TranslucencySortPriority = 1;
	CrossPaperSpriteComp->SetRelativeLocation(FVector(30.f, 0.2f, 10.f));

	// Setup Spring Arm Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetAbsolute(true, true);
	SpringArmComp->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
	
	// Setup Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->PostProcessSettings.bOverride_AutoExposureMethod = true;
	CameraComp->PostProcessSettings.AutoExposureMethod = AEM_Manual;
	CameraComp->PostProcessSettings.bOverride_AutoExposureBias = true;
	CameraComp->PostProcessSettings.AutoExposureBias = 10.2f;
	CameraComp->SetProjectionMode(ECameraProjectionMode::Type::Orthographic);
	CameraComp->SetOrthoWidth(512.f);
	CameraComp->SetAutoCalculateOrthoPlanes(false);
}

void AQDTanukiSamurai::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
	AttackTargetPawn = Cast<AQDToadSamurai>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDToadSamurai::StaticClass()));
}

void AQDTanukiSamurai::OnPhaseChanged(EQDPhase Phase)
{
	Super::OnPhaseChanged(Phase);
	
	switch (Phase)
	{
	case EQDPhase::PlayerStunned:
		SetCrossVisibility(true);
		bCanAttack = false;
		break;
	default:
		break;
	}
}
