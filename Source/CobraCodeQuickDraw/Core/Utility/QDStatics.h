// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "QDStatics.generated.h"

UCLASS(MinimalAPI)
class UQDStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	FORCEINLINE static UMaterialInterface* GetTranslucentUnlitSpriteMaterial()
	{
		return LoadObject<UMaterialInterface>(nullptr, TEXT("/Paper2D/TranslucentUnlitSpriteMaterial.TranslucentUnlitSpriteMaterial"));
	}
	
	FORCEINLINE static UCurveFloat* GetSlideInCurveFloat()
	{
		return LoadObject<UCurveFloat>(nullptr, TEXT("/Game/QuickDraw/Characters/Curve_SamuraiSlideInAlpha_Float.Curve_SamuraiSlideInAlpha_Float"));
	}
};
