// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class PROJECTX_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

	/** The Enhanced Input Mapping Context asset (e.g. IMC_Default) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	// Enable replication for this character
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsSprinting;

	// Input Actions for Enhanced Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Crouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Sprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement methods
	void Move(const struct FInputActionValue& Value); // Handles both forward and right movement
	void Look(const struct FInputActionValue& Value); // Handles camera look input
	void BeginSprint(); // Function to start sprinting
	void EndSprint(); // Function to stop sprinting
	void BeginCrouch(); // Function to start crouching
	void EndCrouch(); // Function to stop crouching
	void BeginJump(); // Function to start jumping
	void EndJump(); // Function to stop jumping

	// Replication properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
