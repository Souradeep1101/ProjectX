// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTaskActor.generated.h"

UCLASS()
class PROJECTX_API AMyTaskActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTaskActor();

	/** Zone for detecting player overlap **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Task")
	class UBoxComponent* TriggerZone;

	/** Completion flag replicated to clients **/
	UPROPERTY(ReplicatedUsing = OnRep_Completed, VisibleAnywhere, BlueprintReadOnly, Category = "Task")
	bool bIsCompleted;

	/** Client calls this to interact with the task **/
	UFUNCTION(Server, Reliable)
	void OnInteract();

protected:
	/** Called on clients when bIsCompleted changes **/
	UFUNCTION()
	void OnRep_Completed();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
