// Fill out your copyright notice in the Description page of Project Settings.


#include "StriderMovementComponent.h"

void UStriderMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
	if (bWantsToCharge)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MaxChargeTime: %f -> AccumCharge: %f"), MaxChargeTime, AccumulatedCharge);
		if (AccumulatedCharge >= MaxChargeTime)
		{
			AccumulatedCharge = MaxChargeTime;
		}
		else
		{
			float alpha = (AccumulatedCharge + DeltaSeconds) / MaxChargeTime;
			AccumulatedCharge = FMath::Lerp(0.0f, MaxChargeTime, alpha);
		}
	}
	else if(!bWantsToCharge && AccumulatedCharge > 0.0f)
	{
		FVector Direction = GetForwardVector();
		float Speed = MinSpeed * AccumulatedCharge;
		FVector VelocityVector = Direction * Speed;
		Launch(VelocityVector);
		bIsSliding = true;							// Character is sliding now
		RemainingSlideTime = AccumulatedCharge;		// Set slide time equal to accumulated charge (room for adjustment)
		AccumulatedCharge = 0.0f;				// Reset charge
		return;
	}
	
	if (bIsSliding)
	{
		if (RemainingSlideTime <= 0.0f)
		{
			RemainingSlideTime = 0.0f;
			bIsSliding = false;
		}
		else
		{
			RemainingSlideTime -= DeltaSeconds;
		}
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


void UStriderMovementComponent::CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration)
{
	if (bIsSliding && RemainingSlideTime > 0.0f)
	{
		UE_LOG(LogTemp, Display, TEXT("Remaining Slide: %f"), RemainingSlideTime);
		Super::CalcVelocity(DeltaTime, 0.0f, bFluid, BrakingDeceleration);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("[%s] NOT Sliding"), *UEnum::GetValueAsString(GetOwnerRole()), Friction);
		Super::CalcVelocity(DeltaTime, Friction, bFluid, BrakingDeceleration);
	}
	
}
