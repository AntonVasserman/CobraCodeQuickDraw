// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CobraCodeQuickDraw/Core/Utility/QuickDrawStatics.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "QDSamuraiPawn.generated.h"

class UPaperSpriteComponent;
class UTimelineComponent;

UCLASS()
class COBRACODEQUICKDRAW_API AQDSamuraiPawn : public APawn
{
	GENERATED_BODY()

public:
	AQDSamuraiPawn();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	FOnTimelineFloat SlideInTimelinePostUpdateDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	UPaperSpriteComponent* PaperSpriteComp;

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

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSlideInTimelinePostUpdate(float Alpha);
	
private:
	FVector SlideInStartLocation;
	FVector SlideInEndLocation;
};
