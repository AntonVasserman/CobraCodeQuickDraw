// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CobraCodeQuickDraw/Core/Characters/QDSamuraiPawn.h"
#include "QDTanukiSamurai.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDTanukiSamurai : public AQDSamuraiPawn
{
	GENERATED_BODY()

public:
	AQDTanukiSamurai();

protected:
	virtual void BeginPlay() override;
};
