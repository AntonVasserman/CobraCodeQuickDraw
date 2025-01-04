// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/QDPawn.h"
#include "QDEnemyPawn.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDEnemyPawn : public AQDPawn
{
	GENERATED_BODY()

public:
	AQDEnemyPawn();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnAttackTargetPawnStunned();
};
