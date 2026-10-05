// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StriderMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERCONTROLLER_API UStriderMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	
	/** Override to enable sliding when DashAction started and completed*/
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	
	/** Override to modify move speed when DashAction is active*/
	virtual float GetMaxSpeed() const override;
	
	/** Override to adjust ground friction when dashing*/
	virtual void CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration) override;
	
	bool bWantsToCharge = false;
	bool bIsSliding = false;
	float AccumulatedCharge = 0.0f;
	float RemainingSlideTime = 0.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxChargeTime = 1.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float MinSpeed = 750.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxSpeed = 1500.0f;
	
};
