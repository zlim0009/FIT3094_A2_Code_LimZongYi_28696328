// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPActor.h"
#include "Components/StaticMeshComponent.h"
#include "StoneMasonActor.generated.h"

/**
 * 
 */
UCLASS()
class FIT3094_A2_CODE_API AStoneMasonActor : public AGOAPActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const int MaxHealth = 100;
	const int MinHealth = 40;
	UPROPERTY(EditAnywhere, Category = "Health")
		int Health;

	const int MaxToolDurability = 75;
	UPROPERTY(EditAnywhere, Category = "Tool")
		int ToolDurability;
	
public:
	// Sets default values for this actor's properties
	AStoneMasonActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function for getting the currently world state. This is virtual as
	// it probably should be overriden by child agents as they will have
	// different information
	TMap<FString, bool> GetWorldState() override;
	// Create a goal state we want to achieve. We could have multiple and pick one
	TMap<FString, bool> CreateGoalState() override;

	// Timed function that decreases health every 2 seconds;
	void DecreaseHealth();

	// Function to heal health to max health
	void Heal() { Health = MaxHealth; }

	// Functions to get health and min health
	int GetHealth() { return Health; }
	int GetMinHealth() { return MinHealth; }

	// Function when actor gets a new tool
	int GetToolDurability() { return ToolDurability; }
	void ResetToolDurability() { ToolDurability = MaxToolDurability; }
	void DecreaseToolDurability() { ToolDurability -= 1; }
	
	// Handle for Timer
	FTimerHandle TimerHandle;

	// Number of stone resources does this actor hold currently
	UPROPERTY(EditAnywhere, Category = "Resources")
	 int NumStoneResources;
};