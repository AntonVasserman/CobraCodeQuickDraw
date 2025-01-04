// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "QDInputStatics.generated.h"

UCLASS(MinimalAPI)
class UQDInputStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	FORCEINLINE static UInputAction* GetAttackInputAction()
	{
		return LoadObject<UInputAction>(nullptr, TEXT("/Game/QuickDraw/Core/Inputs/Actions/IA_Attack.IA_Attack"));
	}

	FORCEINLINE static UInputMappingContext* GetDefaultMappingContext()
	{
		return LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/QuickDraw/Core/Inputs/IMC_Default.IMC_Default"));
	}

	FORCEINLINE static UInputAction* GetDownInputAction()
	{
		return LoadObject<UInputAction>(nullptr, TEXT("/Game/QuickDraw/Core/Inputs/Actions/IA_Down.IA_Down"));
	}

	FORCEINLINE static UInputAction* GetLeftInputAction()
	{
		return LoadObject<UInputAction>(nullptr, TEXT("/Game/QuickDraw/Core/Inputs/Actions/IA_Left.IA_Left"));
	}

	FORCEINLINE static UInputAction* GetRightInputAction()
	{
		return LoadObject<UInputAction>(nullptr, TEXT("/Game/QuickDraw/Core/Inputs/Actions/IA_Right.IA_Right"));
	}

	FORCEINLINE static UInputAction* GetUpInputAction()
	{
		return LoadObject<UInputAction>(nullptr, TEXT("/Game/QuickDraw/Core/Inputs/Actions/IA_Up.IA_Up"));
	}
};
