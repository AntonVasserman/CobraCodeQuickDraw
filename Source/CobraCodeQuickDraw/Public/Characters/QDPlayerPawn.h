// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/QDPawn.h"
#include "Subsystems/QDKeyArrow.h"
#include "QDPlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunned);

// TODO: Consider moving the 3Cs (specifically the Camera) to a Character class as opposed to Pawn class...
UCLASS()
class COBRACODEQUICKDRAW_API AQDPlayerPawn : public AQDPawn
{
	GENERATED_BODY()

public:
	FOnStunned OnStunned;
	AQDPlayerPawn();
	
	virtual void ResetDuel() override;
	void Act(const EQDKeyArrow& KeyArrow) const;
	FORCEINLINE bool CanAct() const { return !bStunned; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* CameraComp;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDrawComboFailed();
	
	UFUNCTION()
	void OnDrawComboSucceeded();

private:
	bool bStunned = false;
};
