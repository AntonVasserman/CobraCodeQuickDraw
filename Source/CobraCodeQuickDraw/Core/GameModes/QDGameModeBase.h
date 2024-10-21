// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QDPhase.h"
#include "GameFramework/GameModeBase.h"
#include "QDGameModeBase.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	FORCEINLINE EQDPhase GetPhase() const { return Phase; }
	
protected:
	UPROPERTY(BlueprintReadWrite)
	EQDPhase Phase = EQDPhase::None;
};
