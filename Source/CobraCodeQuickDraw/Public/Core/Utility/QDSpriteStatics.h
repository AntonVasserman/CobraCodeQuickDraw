// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "QDSpriteStatics.generated.h"

UCLASS(MinimalAPI)
class UQDSpriteStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	FORCEINLINE static UPaperSprite* GetCrossSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Misc/SPR_Cross.SPR_Cross'"));
	}

	FORCEINLINE static UPaperSprite* GetExclamationMarkSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Misc/SPR_Exclamation.SPR_Exclamation'"));
	}
	
	FORCEINLINE static UPaperSprite* GetTanukiAttackSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Tanuki/SPR_Tanuki_Attack.SPR_Tanuki_Attack'"));
	}

	FORCEINLINE static UPaperSprite* GetTanukiDefeatedSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Tanuki/SPR_Tanuki_Defeated.SPR_Tanuki_Defeated'"));
	}

	FORCEINLINE static UPaperSprite* GetTanukiIdleSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Tanuki/SPR_Tanuki_Idle.SPR_Tanuki_Idle'"));
	}

	FORCEINLINE static UPaperSprite* GetToadAttackSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Toad/SPR_Toad_Attack.SPR_Toad_Attack'"));
	}

	FORCEINLINE static UPaperSprite* GetToadDefeatedSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Toad/SPR_Toad_Defeated.SPR_Toad_Defeated'"));
	}

	FORCEINLINE static UPaperSprite* GetToadIdleSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Toad/SPR_Toad_Idle.SPR_Toad_Idle'"));
	}

	FORCEINLINE static UPaperSprite* GetToadMinionAttackSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Toad/SPR_Toad_Minion_Attack.SPR_Toad_Minion_Attack'"));
	}

	FORCEINLINE static UPaperSprite* GetToadMinionDefeatedSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Toad/SPR_Toad_Minion_Defeated.SPR_Toad_Minion_Defeated'"));
	}

	FORCEINLINE static UPaperSprite* GetToadMinionIdleSprite()
	{
		return LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/QuickDraw/Characters/Toad/SPR_Toad_Minion_Idle.SPR_Toad_Minion_Idle'"));
	}
};
