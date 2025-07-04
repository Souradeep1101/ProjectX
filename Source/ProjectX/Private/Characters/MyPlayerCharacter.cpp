// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/MyPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h" // Required for FInputActionValue

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // Enable replication for this character
	bIsSprinting = false; // Initialize sprinting state

	// Set default character movement properties
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Cast to EnhancedInputComponent for enhanced input support
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind Move (Enhanced Input)
		if (IA_Move)
		{
			EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Move);
		}

		// Bind Look (Enhanced Input)
		if (IA_Look)
		{
			EnhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Look);
		}

		// Bind Sprint
		if (IA_Sprint)
		{
			EnhancedInput->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AMyPlayerCharacter::BeginSprint);
			EnhancedInput->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AMyPlayerCharacter::EndSprint);
		}

		// Bind Crouch
		if (IA_Crouch)
		{
			EnhancedInput->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AMyPlayerCharacter::BeginCrouch);
			EnhancedInput->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AMyPlayerCharacter::EndCrouch);
		}

		// Bind Jump
		if (IA_Jump)
		{
			EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMyPlayerCharacter::BeginJump);
			EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AMyPlayerCharacter::EndJump);
		}
	}
}

// Enhanced Input: Move function using FVector2D
void AMyPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller && (MovementVector.X != 0.f || MovementVector.Y != 0.f))
	{
		// Forward/Backward movement
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// Enhanced Input: Look function using FVector2D
void AMyPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller && (LookAxisVector.X != 0.f || LookAxisVector.Y != 0.f))
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


// Function to start sprinting
void AMyPlayerCharacter::BeginSprint()
{
	if (!bIsSprinting)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed *= 1.5f; // Increase speed for sprinting
	}
}

// Function to stop sprinting
void AMyPlayerCharacter::EndSprint()
{
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed /= 1.5f; // Reset speed to normal
	}
}

// Function to start crouching
void AMyPlayerCharacter::BeginCrouch()
{
	if (!bIsCrouched)
	{
		Crouch(); // Call the built-in crouch function
	}
}

// Function to stop crouching
void AMyPlayerCharacter::EndCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch(); // Call the built-in uncrouch function
	}
}

// Function to start jumping
void AMyPlayerCharacter::BeginJump()
{
	if (CanJump())
	{
		bPressedJump = true; // Set the jump flag for Character
	}
}

// Function to stop jumping
void AMyPlayerCharacter::EndJump()
{
	if (bPressedJump)
	{
		bPressedJump = false; // Clear the jump flag
	}
}

// Replication methods for movement and actions
void AMyPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Add properties to replicate here if needed
	// DOREPLIFETIME(AMyPlayerCharacter, MyProperty);

	// Replicate a boolean property for sprinting
	DOREPLIFETIME(AMyPlayerCharacter, bIsSprinting);
}

