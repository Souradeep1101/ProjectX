// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyMonsterPawn.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AMyMonsterPawn::AMyMonsterPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")); // Create the AI Perception Component

	// Configure the AI Perception Component
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2000.0f; // Set sight radius
	SightConfig->LoseSightRadius = 2500.0f; // Set lose sight radius
	SightConfig->PeripheralVisionAngleDegrees = 90.0f; // Set peripheral vision angle
	PerceptionComponent->ConfigureSense(*SightConfig); // Configure the perception component with the sight config
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation()); // Set the dominant sense to sight

}

// Called when the game starts or when spawned
void AMyMonsterPawn::BeginPlay()
{
	Super::BeginPlay();
	// Bind the perception update event
	if (PerceptionComponent)
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMyMonsterPawn::OnPerceptionUpdated);
	}
	
}

// Function to handle perception updates
void AMyMonsterPawn::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// Handle perception updates here
	// For example, you can log the actor and stimulus information
    UE_LOG(LogTemp, Warning, TEXT("Perception Updated: Actor: %s, Stimulus: %s"), *Actor->GetName(), *Stimulus.GetDebugDescription());
	
	// You can also implement custom behavior based on the stimulus
	if (Stimulus.WasSuccessfullySensed())
	{
		// Logic for when the actor is successfully sensed
	}
	else
	{
		// Logic for when the actor is no longer sensed
	}
}

// Called every frame
void AMyMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



