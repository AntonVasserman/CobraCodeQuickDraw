// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "CobraCodeQuickDraw/Core/GameModes/QDGameModeBase.h"
#include "CobraCodeQuickDraw/Core/Utility/QuickDrawStatics.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "QDSamuraiPawn.generated.h"

class UTimelineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAwaitingDuel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackSucceeded, bool, bIsPlayer);

UCLASS()
class COBRACODEQUICKDRAW_API AQDSamuraiPawn : public APawn
{
	GENERATED_BODY()

public:
	FOnAwaitingDuel OnAwaitingDuel;
	FOnAttackSucceeded OnAttackSucceeded;
	
	AQDSamuraiPawn();
	
	void Attack();
	void Defeated();
	FORCEINLINE bool CanAttack() const { return bCanAttack; }
	FORCEINLINE bool IsAwaitingDuel() const { return bAwaitingDuel; }
	virtual void OnConstruction(const FTransform& Transform) override;
	void ResetDual();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	FORCEINLINE void SetCrossVisibility(const bool bVisibility) const { CrossPaperSpriteComp->SetVisibility(bVisibility); }

protected:
	FOnTimelineFloat SlideInTimelineUpdateDelegate;
	FOnTimelineEvent SlideInTimelineFinishedDelegate;
	FOnTimelineFloat AttackUpdateDelegate;
	FOnTimelineEvent AttackEventDelegate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AQDGameModeBase* GameModeRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* PaperSpriteComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* CrossPaperSpriteComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSprite* AttackSprite = UQuickDrawStatics::GetTanukiAttackSprite(); // If a sprite isn't set, we default to the Tanuki sprite

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSprite* DefeatedSprite = UQuickDrawStatics::GetTanukiDefeatedSprite(); // If a sprite isn't set, we default to the Tanuki sprite
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSprite* IdleSprite = UQuickDrawStatics::GetTanukiIdleSprite(); // If a sprite isn't set, we default to the Tanuki sprite 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide In Animation")
	UBillboardComponent* SlideInEndBillboardComp;

	UPROPERTY(BlueprintReadOnly, Category = "Slide In Animation")
	UTimelineComponent* SlideInTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide In Animation")
	UCurveFloat* SlideInCurveFloat = UQuickDrawStatics::GetSlideInCurveFloat();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slide In Animation")
	float SlideInPlayRate = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Animation")
	UBillboardComponent* AttackEndBillboardComp;

	UPROPERTY(BlueprintReadOnly, Category = "Attack Animation")
	UTimelineComponent* AttackTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Animation")
	UCurveFloat* AttackCurveFloat = UQuickDrawStatics::GetSlideInCurveFloat();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Animation")
	float AttackPlayRate = 8.f;

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
	bool bCanAttack = false;
	
	FVector SlideInStartLocation;
	FVector SlideInEndLocation;
	FVector AttackEndLocation;
};
