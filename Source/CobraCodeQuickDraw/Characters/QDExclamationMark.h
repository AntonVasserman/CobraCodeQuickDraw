// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "QDExclamationMark.generated.h"

class UPaperSpriteComponent;

UCLASS()
class COBRACODEQUICKDRAW_API AQDExclamationMark : public AActor
{
	GENERATED_BODY()
	
public:	
	AQDExclamationMark();

	FORCEINLINE void SetVisibility(const bool bNewVisibility) { SpriteComp->SetVisibility(bNewVisibility); }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComp;
};
