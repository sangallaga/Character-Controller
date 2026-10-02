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
	
	/** Override to modify move speed when actively DashAction*/
	virtual float GetMaxSpeed() const override;
	
	bool bWantsToCharge = false;
	float AccumulatedCharge = 0.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxChargeTime = 1.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float MinSpeed = 500.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxSpeed = 600.0f;
	
};
