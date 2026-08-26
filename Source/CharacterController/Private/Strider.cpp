// Fill out your copyright notice in the Description page of Project Settings.


#include "Strider.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AStrider::AStrider()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrider::BeginPlay()
{
	Super::BeginPlay();
	
	// Add custom MappingContext to local player
	// 
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void AStrider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStrider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStrider::Move);
		EIC->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AStrider::Rotate);
	}

}

// Called to translate player's current location (MoveAction Triggered)
void AStrider::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	// Instantiate controller's rot
	const FRotator ControlRot = Controller->GetControlRotation();
	const FRotator ControlYaw(0.f, ControlRot.Yaw, 0.f); // Create FRotator based off ControlRot's pure yaw (no pitch no roll)
	const FVector Forward = FRotationMatrix(ControlYaw).GetUnitAxis(EAxis::X); // Create FVector from Controller's forward vector
	const FVector Right = FRotationMatrix(ControlYaw).GetUnitAxis(EAxis::Y);
	AddMovementInput(Forward, MovementVector.Y);
	AddMovementInput(Right, MovementVector.X);
	
	// Dev Tool to display current location per keystroke
	//RepLoc();
}

// Helper function to UE_LOG current location to dispaly
void AStrider::RepLoc()
{
	FVector CurrentLocation = GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("Curr Loc - X: %f, Y: %f, Z: %f"),
		CurrentLocation.X,
		CurrentLocation.Y,
		CurrentLocation.Z);
}

// Called to enable looking 
void AStrider::Rotate(const FInputActionValue& Value)
{
	// Transform Value into FVector2D to manipulate character pitch and yaw
	const FVector2D RotateVector = Value.Get<FVector2D>();
	AddControllerYawInput(RotateVector.X);
	AddControllerPitchInput(RotateVector.Y);
}


