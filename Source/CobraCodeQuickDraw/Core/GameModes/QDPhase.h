// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EQDPhase : uint8
{
	Intro		UMETA(DisplayName = "Intro", Description = "Players sliding in"),
	Wait		UMETA(DisplayName = "Wait", Description = "Waiting for round start, but accepting input"),
	Draw		UMETA(DisplayName = "Draw", Description = "Allowing Attack"),
	Finished	UMETA(DisplayName = "Finished", Description = "Round finished"),
};
