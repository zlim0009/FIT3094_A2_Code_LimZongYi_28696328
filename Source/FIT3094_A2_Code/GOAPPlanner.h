// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Queue.h"
#include "CoreMinimal.h"

// Forward Declaration is done in header file
// Avoids circular dependency
class AGOAPActor;
class GOAPAction;

// We use a basic struct called a GOAP Node when planning
// This function fairly similar to our GridNode from previous weeks
// Used when building search graph in planner
struct GOAPNode
{
	// Where it came from
	GOAPNode* Parent;
	// Cost so far to reach this point
	float RunningCost;
	// Current state of the world when reaching this point
	TMap<FString, bool> State;
	// A node is associated with an action. This is that action
	GOAPAction* Action;
};

/**
 * 
 */
class FIT3094_A2_CODE_API GOAPPlanner
{
public:
	GOAPPlanner();
	~GOAPPlanner();

	// Function called to generate the action plan
	// The Agent calling it passed itself through along with its Available Actions
	// and Action Queue
	static bool Plan(AGOAPActor* Agent, const TSet<GOAPAction*>& AvailableActions,
		TQueue<GOAPAction*>& PlannedActions, TMap<FString, bool> WorldState,
		TMap<FString, bool> GoalState);

protected:
	// Function builds out hte node graph until it exhausts all possible paths
	// It uses a combination of A* and brute force to do this as well. It could be optimized.
	// Calls itself recursively to build out nodes in the graph and find goals
	// Again not well optimized so should be used carefully
	static bool BuildGraphRecursive(TArray<GOAPNode*>& AllNodes, GOAPNode* Parent,
		TArray<GOAPNode*>& GoalNodes, const TSet<GOAPAction*>& AvailableActions,
		TMap<FString, bool>& GoalState);

	// Function used for creating a subset of actions with an action removed. This is used
	// to reduce available actions as more are checked off the list (aka don't call the same action twice)
	// Do note this could potentially cause issues later if you wanted to call the same action twice
	static TSet<GOAPAction*> CreateActionSubset(const TSet<GOAPAction*>& AvailableActions,
		GOAPAction* RemoveAction);

	// Function compares a set of conditions to a state. Used to both determine if goals are met
	// and also if preconditions match existing world state
	static bool CheckConditionsInState(TMap<FString, bool>& Conditions,
		TMap<FString, bool>& State);

	// Combine a current state with changes (aka effects) of an action
	static TMap<FString, bool> PopulateNewState(const TMap<FString, bool>& CurrentState,
		TMap<FString, bool>& Changes);
};
