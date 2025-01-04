// Copyright Anton Vasserman, All Rights Reserved.

#include "Characters/QDPlayerPawn.h"

#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/QDEnemyPawn.h"
#include "Core/GameModes/GameStates/QDGameStateBase.h"
#include "Core/Utility/QDSpriteStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/QDDrawWorldSubsystem.h"

AQDPlayerPawn::AQDPlayerPawn()
{
	AttackSprite = UQDSpriteStatics::GetTanukiAttackSprite();
	DefeatedSprite = UQDSpriteStatics::GetTanukiDefeatedSprite();
	IdleSprite = UQDSpriteStatics::GetTanukiIdleSprite();
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

void AQDPlayerPawn::ResetDuel()
{
	Super::ResetDuel();

	bStunned = false;
}

void AQDPlayerPawn::Act(const EQDKeyArrow& KeyArrow) const
{
	switch (GameStateRef->GetPhase())
	{
	case EQDPhase::Draw:
		GetWorld()->GetSubsystem<UQDDrawWorldSubsystem>()->AddKeyArrowToCombo(KeyArrow);
		break;
	default:
		break;
	}
}

void AQDPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
	AttackTargetPawn = Cast<AQDEnemyPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AQDEnemyPawn::StaticClass()));

	UQDDrawWorldSubsystem* DrawSubsystem = GetWorld()->GetSubsystem<UQDDrawWorldSubsystem>();
	DrawSubsystem->OnDrawComboFailed.AddDynamic(this, &AQDPlayerPawn::OnDrawComboFailed);
	DrawSubsystem->OnDrawComboSucceeded.AddDynamic(this, &AQDPlayerPawn::OnDrawComboSucceeded);
}

void AQDPlayerPawn::OnDrawComboFailed()
{
	bStunned = true;
	SetCrossVisibility(true);
	bCanAttack = false;
	OnStunned.Broadcast();
}

void AQDPlayerPawn::OnDrawComboSucceeded()
{
	Attack();
}
