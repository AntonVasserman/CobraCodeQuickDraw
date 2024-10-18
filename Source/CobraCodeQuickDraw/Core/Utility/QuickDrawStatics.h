// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "QuickDrawStatics.generated.h"

UCLASS(MinimalAPI)
class UQuickDrawStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	FORCEINLINE static UPaperSprite* GetTanukiIdleSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Tanuki/SPR_Tanuki_Idle.SPR_Tanuki_Idle'"));
	}
	FORCEINLINE static UPaperSprite* GetToadIdleSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Toad/SPR_Toad_Idle.SPR_Toad_Idle'"));
	}
	FORCEINLINE static UMaterialInterface* GetTranslucentUnlitSpriteMaterial()
	{
		return LoadObject<UMaterialInterface>(nullptr, TEXT("/Paper2D/TranslucentUnlitSpriteMaterial.TranslucentUnlitSpriteMaterial"));
	}
	FORCEINLINE static UCurveFloat* GetSlideInCurveFloat()
	{
		return LoadObject<UCurveFloat>(nullptr, TEXT("/Game/QuickDraw/Characters/Curve_SamuraiSlideInAlpha_Float.Curve_SamuraiSlideInAlpha_Float"));
	}
	FORCEINLINE static UTexture* GetTargetPointTexture()
	{
		return LoadObject<UTexture>(nullptr, TEXT("/Engine/EditorResources/S_TargetPoint.S_TargetPoint"));
	}
};
