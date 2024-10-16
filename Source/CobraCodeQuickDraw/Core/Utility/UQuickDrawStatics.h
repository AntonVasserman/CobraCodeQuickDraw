// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "UQuickDrawStatics.generated.h"

UCLASS(MinimalAPI)
class UQuickDrawStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	FORCEINLINE static UPaperSprite* GetTanukiIdleSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Tanuki/SPR_Tanuki_Idle.SPR_Tanuki_Idle'"));
	}
	FORCEINLINE static UMaterialInterface* GetTranslucentUnlitSpriteMaterial()
	{
		return LoadObject<UMaterialInterface>(nullptr, TEXT("/Paper2D/TranslucentUnlitSpriteMaterial.TranslucentUnlitSpriteMaterial"));
	}
};
