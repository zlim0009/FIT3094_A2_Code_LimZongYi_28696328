// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "GOAPAction.h"
#include "StateMachine.h"
#include "GOAPActor.generated.h"

UCLASS()
class FIT3094_A2_CODE_API AGOAPActor : public AActor
{
	GENERATED_BODY()
	
public:
	enum Actor_States
	{
		State_Nothing,
		State_Idle,
		State_Move,
		State_Action
	};

	// Sets default values for this actor's properties
	AGOAPActor();

private:
	// Variable for handling movement
	const float Tolerance = 20;
	float MoveSpeed;

protected:
	// State Machine
	StateMachine<Actor_States, AGOAPActor>* ActionStateMachine;

	// List of all available actions this Agent can do
	TSet<GOAPAction*> AvailableActions;
	// Set of actions that the agent is currently planning to use
	TQueue<GOAPAction*> CurrentActions;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// State Machine Functions
	void OnIdleEnter();
	void OnIdleUpdate(float DeltaTime);
	void OnIdleExit();

	void OnMoveEnter();
	void OnMoveUpdate(float DeltaTime);
	void OnMoveExit();

	void OnActionEnter();
	void OnActionUpdate(float DeltaTime);
	void OnActionExit();

	// Function for getting the currently world state. This is virtual as
	// it probably should be overriden by child agents as they will have
	// different information
	virtual TMap<FString, bool> GetWorldState();
	// Create a goal state we want to achieve. We could have multiple and pick one
	virtual TMap<FString, bool> CreateGoalState();
	// A plan was unable to be found. Handle this behaviour (Probably just Idle)
	virtual void OnPlanFailed(TMap<FString, bool> FailedGoalState);
	// A plan was aborted mid way. The provided action failed to execute
	// Handle this behaviour in some way
	virtual void OnPlanAborted(GOAPAction* FailedAction);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	GOAPAction* GetCurrentAction() { return *CurrentActions.Peek(); }
};
