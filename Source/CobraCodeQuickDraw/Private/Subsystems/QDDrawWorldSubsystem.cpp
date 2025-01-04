// Copyright Anton Vasserman, All Rights Reserved.

#include "Subsystems/QDDrawWorldSubsystem.h"

#include "Core/GameModes/GameStates/QDGameStateBase.h"

void UQDDrawWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	GameStateRef = InWorld.GetGameState<AQDGameStateBase>();
	GameStateRef->OnPhaseChanged.AddDynamic(this, &UQDDrawWorldSubsystem::OnPhaseChanged);
}

void UQDDrawWorldSubsystem::AddKeyArrowToCombo(EQDKeyArrow KeyArrow)
{
	if (KeyArrow != CurrentKeyArrows[Current])
	{
		OnDrawComboFailed.Broadcast();
		bAcceptingInput = false;
	}
	else
	{
		Current++;
	
		if (Current == CurrentKeyArrows.Num())
		{
			OnDrawComboSucceeded.Broadcast();
			bAcceptingInput = false;
		}
	}
}

void UQDDrawWorldSubsystem::OnPhaseChanged(EQDPhase Phase)
{
	switch (Phase)
	{
	case EQDPhase::Intro:
	case EQDPhase::Wait:
		bAcceptingInput = false;
		GenerateKeyArrows(1);
		break;
	case EQDPhase::Draw:
		// TODO: Remove this in favor of Widgets
		DrawKeyArrows(1);
		bAcceptingInput = true;
		break;
	case EQDPhase::Finished:
		bAcceptingInput = false;
		break;
	default:
		break;
	}
}

void UQDDrawWorldSubsystem::DrawKeyArrows(int Count)
{
	if (GEngine)
	{
		for (int i = 0; i < Count; i++)
		{
			FString NextInputKey = StaticEnum<EQDKeyArrow>()->GetNameStringByValue(static_cast<uint8>(CurrentKeyArrows[i]));
			GEngine->AddOnScreenDebugMessage(i + 1, 3, FColor::Red, FString::Printf(TEXT("%d: %s"), i, *NextInputKey));
		}
	}
}

void UQDDrawWorldSubsystem::GenerateKeyArrows(int Count)
{
	Current = 0;
	CurrentKeyArrows.Empty();
	
	for (int i = 0; i < Count; i++)
	{
		// Generate a random integer within the range of the enum values
		int32 RandomIndex = FMath::RandRange(0, static_cast<int32>(EQDKeyArrow::Up));
		EQDKeyArrow RandomValue = static_cast<EQDKeyArrow>(RandomIndex);

		// Add the random value to the TArray
		CurrentKeyArrows.Add(RandomValue);
	}
}
