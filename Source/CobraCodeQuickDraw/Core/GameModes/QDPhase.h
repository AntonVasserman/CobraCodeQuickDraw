// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EQDPhase : uint8
{
	None			UMETA(DisplayName = "None", Description = "Duel hasn't started yet"),
	Intro			UMETA(DisplayName = "Intro", Description = "Players sliding in"),
	Wait			UMETA(DisplayName = "Wait", Description = "Waiting for round start, but accepting input"),
	PlayerStunned	UMETA(DisplayName = "PlayerStunned", Description = "Player samurai became stunned"),
	Draw			UMETA(DisplayName = "Draw", Description = "Allowing Attack"),
	Finished		UMETA(DisplayName = "Finished", Description = "Round finished"),
};
