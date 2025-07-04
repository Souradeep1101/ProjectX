// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyMonsterPawn.generated.h"

UCLASS()
class PROJECTX_API AMyMonsterPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyMonsterPawn();
	
	// AI Perception Component to handle perception events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAIPerceptionComponent* PerceptionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Function to handle perception updates
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
