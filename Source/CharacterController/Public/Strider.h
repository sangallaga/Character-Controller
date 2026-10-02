// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Strider.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class UStriderMovementComponent;

UCLASS()
class CHARACTERCONTROLLER_API AStrider : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStrider(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> RotateAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> DashAction;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;
	
	UPROPERTY()
	TObjectPtr<UStriderMovementComponent> StriderMovement;
	
	void Move(const FInputActionValue& Value);
	
	void Rotate(const FInputActionValue& Value);
	
	void RepLoc();
	
	void Dash(const FInputActionValue& Value);
	
	void StopDashing(const FInputActionValue& Value);
	
	

};
