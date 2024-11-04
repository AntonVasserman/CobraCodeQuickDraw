// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDPhase.h"
#include "CobraCodeQuickDraw/Core/Utility/QDStatics.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "QDSamuraiPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAwaitingDuel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDefeated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunned);

UCLASS()
class COBRACODEQUICKDRAW_API AQDSamuraiPawn : public APawn
{
	GENERATED_BODY()

public:
	FOnAwaitingDuel OnAwaitingDuel;
	FOnDefeated OnDefeated;
	FOnStunned OnStunned;
	
	AQDSamuraiPawn();
	virtual void Attack();
	void Defeated();
	FORCEINLINE bool CanAttack() const { return bCanAttack; }
	FORCEINLINE bool IsAwaitingDuel() const { return bAwaitingDuel; }
	virtual void PostInitProperties() override;
	void ResetDual();
	FORCEINLINE void SetCrossVisibility(const bool bVisibility) const { CrossPaperSpriteComp->SetVisibility(bVisibility); }

protected:
	FOnTimelineFloat SlideInTimelineUpdateDelegate;
	FOnTimelineEvent SlideInTimelineFinishedDelegate;
	FOnTimelineFloat AttackUpdateDelegate;
	FOnTimelineEvent AttackEventDelegate;
	
	UPROPERTY(BlueprintReadOnly)
	class AQDGameStateBase* GameStateRef = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category=Sprite)
	UPaperSpriteComponent* PaperSpriteComp;

	UPROPERTY(BlueprintReadOnly, Category=Sprite)
	UPaperSpriteComponent* CrossPaperSpriteComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sprite)
	UPaperSprite* AttackSprite = UQDStatics::GetTanukiAttackSprite(); // If a sprite isn't set, we default to the Tanuki sprite

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sprite)
	UPaperSprite* DefeatedSprite = UQDStatics::GetTanukiDefeatedSprite(); // If a sprite isn't set, we default to the Tanuki sprite
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sprite)
	UPaperSprite* IdleSprite = UQDStatics::GetTanukiIdleSprite(); // If a sprite isn't set, we default to the Tanuki sprite 

	UPROPERTY(BlueprintReadOnly, Category="Slide In Animation")
	UTimelineComponent* SlideInTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Slide In Animation")
	UCurveFloat* SlideInCurveFloat = UQDStatics::GetSlideInCurveFloat();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Slide In Animation")
	float SlideInPlayRate = 2.f;

	UPROPERTY(BlueprintReadOnly, Category="Attack Animation")
	UTimelineComponent* AttackTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack Animation")
	UCurveFloat* AttackCurveFloat = UQDStatics::GetSlideInCurveFloat();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack Animation")
	float AttackPlayRate = 8.f;

	bool bCanAttack = false;
	TWeakObjectPtr<AQDSamuraiPawn> AttackTargetPawn = nullptr;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPhaseChanged(EQDPhase Phase);
	UFUNCTION()
	void OnSlideInTimelineFinished();
	UFUNCTION()
	void OnSlideInTimelineUpdate(float Alpha);
	UFUNCTION()
	void OnAttackTimelineUpdate(float Alpha);
	UFUNCTION()
	void OnAttackTimelineEvent();
	
private:
	bool bAwaitingDuel = false;
	float SlideInAlphaFromCenter = 0.75f;
	FVector SlideInStartLocation;
	FVector SlideInEndLocation;
	float AttackAlphaFromTarget = 0.65f;
	FVector AttackEndLocation;
};
