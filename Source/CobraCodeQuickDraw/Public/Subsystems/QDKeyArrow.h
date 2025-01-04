// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EQDKeyArrow : uint8
{
	Down	UMETA(DisplayName = "Down", Description = "Down Key Arrow"),
	Left	UMETA(DisplayName = "Left", Description = "Left Key Arrow"),
	Right	UMETA(DisplayName = "Right", Description = "Right Key Arrow"),
	Up		UMETA(DisplayName = "Up", Description = "Up Key Arrow"),
};
