// Fill out your copyright notice in the Description page of Project Settings.


#include "StriderMovementComponent.h"

void UStriderMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
	if (bWantsToCharge)
	{
		//UE_LOG(LogTemp, Warning, TEXT("DeltaSeconds: %f"), DeltaSeconds);
		if (AccumulatedCharge >= MaxChargeTime)
		{
			AccumulatedCharge = MaxChargeTime;
		}
		else
		{
			float alpha = (AccumulatedCharge + DeltaSeconds) / MaxChargeTime;
			AccumulatedCharge = FMath::Lerp(0.0f, MaxChargeTime, alpha);
			//UE_LOG(LogTemp, Warning, TEXT("ChargeTime: %f"), AccumulatedCharge);
		}
		UE_LOG(LogTemp, Warning, TEXT("ChargeTime: %f"), AccumulatedCharge);
	}
	
	if (!bWantsToCharge)
	{
		FVector Direction = GetForwardVector();
		float Speed = 500.0f * AccumulatedCharge;
		FVector VelocityVector = Direction * Speed;
		Launch(VelocityVector);	
		AccumulatedCharge = 0.0f;
	}

}

float UStriderMovementComponent::GetMaxSpeed() const
{
	if (bWantsToCharge)
	{
		float BaseMaxSpeed = Super::GetMaxSpeed();
		float MoveSlowDelta = FMath::GetMappedRangeValueClamped(
			FVector2D(0.0f, MaxChargeTime),
			FVector2D(1.0f, 0.01),
			AccumulatedCharge);
		return BaseMaxSpeed * MoveSlowDelta;
	}
	return Super::GetMaxSpeed();
}

