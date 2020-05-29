// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPActor.h"
#include "GOAPPlanner.h"

// Sets default values
AGOAPActor::AGOAPActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActionStateMachine = new StateMachine<Actor_States, AGOAPActor>(this, State_Nothing);
	ActionStateMachine->RegisterState(State_Idle, &AGOAPActor::OnIdleEnter, &AGOAPActor::OnIdleUpdate, &AGOAPActor::OnIdleExit);
	ActionStateMachine->RegisterState(State_Action, &AGOAPActor::OnActionEnter, &AGOAPActor::OnActionUpdate, &AGOAPActor::OnActionExit);
	ActionStateMachine->RegisterState(State_Move, &AGOAPActor::OnMoveEnter, &AGOAPActor::OnMoveUpdate, &AGOAPActor::OnMoveExit);
	ActionStateMachine->ChangeState(State_Idle);

	MoveSpeed = 1000;
}

// Called when the game starts or when spawned
void AGOAPActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGOAPActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActionStateMachine->Tick(DeltaTime);
}

// State Machine Functions
void AGOAPActor::OnIdleEnter() {}

void AGOAPActor::OnIdleUpdate(float DeltaTime)
{
	// Planning next move
	// Get World State
	TMap<FString, bool> WorldState = GetWorldState();
	// Get Desired Goal State
	TMap<FString, bool> GoalState = CreateGoalState();

	// Attempt to make plan and check success
	if (GOAPPlanner::Plan(this, AvailableActions, CurrentActions, WorldState, GoalState))
	{
		UE_LOG(LogTemp, Warning, TEXT("GOAP ACTOR CLASS: Plan has been found"));
		ActionStateMachine->ChangeState(State_Action);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GOAP ACTOR CLASS: No Plan Found"))
	}
}

void AGOAPActor::OnIdleExit() {}


void AGOAPActor::OnMoveEnter()
{
	// Entering into move state check to ensure we can move
	// If no actions return to idle immediately
	if (CurrentActions.IsEmpty())
	{
		ActionStateMachine->ChangeState(State_Idle);
	}

	// If current action requires an InRange check AND the target is NULL. Return to planning
	GOAPAction* CurrentAction = *CurrentActions.Peek();
	if (CurrentAction->RequireInRange() && CurrentAction->Target == nullptr)
	{
		ActionStateMachine->ChangeState(State_Idle);
	}
}

void AGOAPActor::OnMoveUpdate(float DeltaTime)
{
	GOAPAction* CurrentAction = *CurrentActions.Peek();

	// This is a direct movement example
	// For assignment use pathfinding and grid based movement here
	FVector Direction = CurrentAction->Target->GetActorLocation() - GetActorLocation();
	Direction.Normalize();

	// Update position based on direction and move speed
	FVector NewPos = GetActorLocation() + Direction * MoveSpeed * DeltaTime;

	// If we are close enough to target then snap to it
	if (FVector::Dist(NewPos, CurrentAction->Target->GetActorLocation()) <= Tolerance)
	{
		NewPos = CurrentAction->Target->GetActorLocation();
		// We are now in range of taget so set it ot true
		CurrentAction->SetInRange(true);
		ActionStateMachine->ChangeState(State_Action);
	}

	SetActorLocation(NewPos);
}


void AGOAPActor::OnMoveExit() {}


void AGOAPActor::OnActionEnter() {}

void AGOAPActor::OnActionUpdate(float DeltaTime)
{
	// If we have no state change to idle and exit immediately
	if (CurrentActions.IsEmpty())
	{
		ActionStateMachine->ChangeState(State_Idle);
		return;
	}

	GOAPAction* CurrentAction = *CurrentActions.Peek();
	if (CurrentAction->IsActionDone())
	{
		// We are done with this action
		CurrentActions.Dequeue(CurrentAction);
	}

	if (!CurrentActions.IsEmpty())
	{
		// Get top of queue
		// It is technically a pointer which is why we dereference one layer
		CurrentAction = *CurrentActions.Peek();

		// Check to see if we need to be within range for and action
		// If no range requirement is needed, return true
		// If a range requirement does exist then check to see if we are in range
		// Ternary operators are nasty but they do have their place
		bool InRange = CurrentAction->RequireInRange() ? CurrentAction->IsInRange() : true;

		// If in range, attempt to do action
		if (InRange)
		{
			// Attempt to perform action
			// Action can fail which is why we store the result
			bool IsActionSuccessful = CurrentAction->PerformAction(this);
			UE_LOG(LogTemp, Warning, TEXT("GOAP ACTOR CLASS: Action performed"));

			// If we fail change to the idle state and report that we had to abort the plan
			if (!IsActionSuccessful)
			{
				ActionStateMachine->ChangeState(State_Idle);
				OnPlanAborted(CurrentAction);
			}
		}
		else
		{
			// At this point we have a valid action but are not in range. Commence movement
			ActionStateMachine->ChangeState(State_Move);
		}
	}
	else
	{
		// No actions remaining move to idle state
		ActionStateMachine->ChangeState(State_Idle);
	}
}

void AGOAPActor::OnActionExit() {}


TMap<FString, bool> AGOAPActor::GetWorldState()
{
	TMap<FString, bool> CurrentWorldState;
	return CurrentWorldState;
}

TMap<FString, bool> AGOAPActor::CreateGoalState()
{
	TMap<FString, bool> GoalState;
	return GoalState;
}

void AGOAPActor::OnPlanFailed(TMap<FString, bool> FailedGoalState)
{
	UE_LOG(LogTemp, Warning, TEXT("GOAP ACTOR CLASS: Plan Failed"));
}


void AGOAPActor::OnPlanAborted(GOAPAction* FailedAction)
{
	UE_LOG(LogTemp, Warning, TEXT("GOAP ACTOR CLASS: Plan Aborted"));
}
