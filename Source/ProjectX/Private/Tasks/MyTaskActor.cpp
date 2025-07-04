// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/MyTaskActor.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyTaskActor::AMyTaskActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // Enable replication for this actor
	bIsCompleted = false; // Initialize completion flag

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone")); // Create the trigger zone component
	TriggerZone->SetupAttachment(GetRootComponent()); // Set the root component to the trigger zone
	TriggerZone->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore all collisions by default
	TriggerZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Set overlap response for pawns

}

void AMyTaskActor::OnInteract_Implementation()
{
	// This function is called on the server when a client interacts with the task
	if (!bIsCompleted)
	{
		bIsCompleted = true; // Mark the task as completed
		OnRep_Completed(); // Call the replication function to notify clients
	}
}


void AMyTaskActor::OnRep_Completed()
{
	// This function is called on clients when bIsCompleted changes
	if (bIsCompleted)
	{
		// Handle task completion logic here, e.g., notify players, update UI, etc.
		UE_LOG(LogTemp, Warning, TEXT("Task completed!"));
	}
}

void AMyTaskActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate the bIsCompleted variable to clients
	DOREPLIFETIME(AMyTaskActor, bIsCompleted);
}

// Called every frame
void AMyTaskActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

