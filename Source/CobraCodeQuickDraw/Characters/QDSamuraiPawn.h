// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "QDSamuraiPawn.generated.h"

UCLASS()
class COBRACODEQUICKDRAW_API AQDSamuraiPawn : public APawn
{
	GENERATED_BODY()

public:
	AQDSamuraiPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprite)
	class UPaperSpriteComponent* PaperSpriteComp;
	
	virtual void BeginPlay() override;
};
