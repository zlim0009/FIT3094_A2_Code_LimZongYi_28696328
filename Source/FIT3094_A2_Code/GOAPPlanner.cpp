// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPPlanner.h"
#include "GOAPAction.h"
#include "GOAPActor.h"

GOAPPlanner::GOAPPlanner()
{
	// Nothing
}

GOAPPlanner::~GOAPPlanner()
{
	// Same
}


bool GOAPPlanner::Plan(AGOAPActor* Agent, const TSet<GOAPAction*>& AvailableActions,
	TQueue<GOAPAction*>& PlannedActions, TMap<FString, bool> WorldState,
	TMap<FString, bool> GoalState)
{
	// Start of planning we create an array to hold all nodes generated during planning
	TArray<GOAPNode*> AllNodes;

	// Reset akk action states
	for (auto Action : AvailableActions)
	{
		Action->DoReset();
	}

	// Clear Planned Action Queue
	PlannedActions.Empty();

	// Get usable actions
	TSet<GOAPAction*> UsableActions;
	for (auto Action : AvailableActions)
	{
		if (Action->CheckProceduralPrecondition(Agent))
		{
			UsableActions.Add(Action);
		}
	}

	// Build tree of actions
	// Create TArray of Goal Nodes
	TArray<GOAPNode*> GoalNodes;

	// Define Start Node
	GOAPNode* Start = new GOAPNode;
	Start->Parent = nullptr;
	Start->RunningCost = 0;
	Start->State = WorldState;
	Start->Action = nullptr;

	// Call BuildGraph function (returns true or false depending on if goal was found)
	bool IsSuccessful = BuildGraphRecursive(AllNodes, Start, GoalNodes,
		UsableActions, GoalState);

	// Check for success
	// If not successful then return immediately
	if (!IsSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("GOAP PLANNER: No Plan Found"));
		return false;
	}

	// Get the cheapest goal
	GOAPNode* CheapestNode = nullptr;
	for (auto Node : GoalNodes)
	{
		if (CheapestNode)
		{
			if (Node->RunningCost < CheapestNode->RunningCost)
			{
				CheapestNode = Node;
			}
		}
		else
		{
			CheapestNode = Node;
		}
	}

	// Work back from cheapest goal to start
	TArray<GOAPAction*> Results;
	GOAPNode* CurrentNode = CheapestNode;

	// While the current node is not null loop
	// Eventually we will reach the start node which has a null parent
	while (CurrentNode)
	{
		if (CurrentNode->Action)
		{
			Results.Insert(CurrentNode->Action, 0);
		}
		CurrentNode = CurrentNode->Parent;
	}

	//Build queue from results
	for (auto Action : Results)
	{
		PlannedActions.Enqueue(Action);
	}

	// Clean up nodes
	AllNodes.Empty();

	// Plan succeeded
	return true;
}


bool GOAPPlanner::BuildGraphRecursive(TArray<GOAPNode*>& AllNodes,
	GOAPNode* Parent, TArray<GOAPNode*>& GoalNodes,
	const TSet<GOAPAction*>& UsableActions, TMap<FString, bool>& GoalState)
{
	// Have we found the goal at this time or in a child call
	bool HasFoundGoal = false;

	// For ever action that is available
	for (auto Action : UsableActions)
	{
		// Check to see if the preconditions of a state allow it to run
		if (CheckConditionsInState(Action->Preconditions, Parent->State))
		{
			// Create a new updated world state based on current state and action effects
			TMap<FString, bool> CurrentState = PopulateNewState(Parent->State,
				Action->Effects);

			// Create a new GOAP Node object for this action and position in graph
			GOAPNode* Node = new GOAPNode;
			Node->Parent = Parent;
			Node->RunningCost = Parent->RunningCost + Action->ActionCost;
			Node->State = CurrentState;
			Node->Action = Action;

			// Add it to our main list of nodes for deletion later
			AllNodes.Add(Node);

			// Check conditions to see if we have a match for our goal
			if (CheckConditionsInState(GoalState, CurrentState))
			{
				// Found Goal
				GoalNodes.Add(Node);
				HasFoundGoal = true;
			}
			else
			{
				// Create a new subset of available actions without the current state
				TSet<GOAPAction*> ActionSubset = CreateActionSubset(UsableActions, Action);
				// Call this function recursively until we run out of actions
				HasFoundGoal = BuildGraphRecursive(AllNodes, Node, GoalNodes, ActionSubset, GoalState);
			}
		}
	}

	return HasFoundGoal;
}


TSet<GOAPAction*> GOAPPlanner::CreateActionSubset(const TSet<GOAPAction*>& UsableActions,
	GOAPAction* RemoveAction)
{
	// Create a subset of actions without the provided action
	TSet<GOAPAction*> NewActionSet;

	for (auto Action : UsableActions)
	{
		if (Action != RemoveAction)
		{
			NewActionSet.Add(Action);
		}
	}

	return NewActionSet;
}


bool GOAPPlanner::CheckConditionsInState(TMap<FString, bool>& Conditions,
	TMap<FString, bool>& State)
{
	// Check to see if the first set of conditions exist in the provided world state
	for (auto Condition : Conditions)
	{
		bool* CurrentStateCondition = State.Find(Condition.Key);

		if (CurrentStateCondition)
		{
			if (Condition.Value != *CurrentStateCondition)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}


TMap<FString, bool> GOAPPlanner::PopulateNewState(const TMap<FString,
	bool>& CurrentState, TMap<FString, bool>& Changes)
{
	// Generate a new state based on current state
	TMap<FString, bool> NewState = CurrentState;

	// Make changes based on updated changes
	// These are generally an action's effects
	for (auto Pairs : Changes)
	{
		NewState.Add(Pairs.Key, Pairs.Value);
	}

	return NewState;
}