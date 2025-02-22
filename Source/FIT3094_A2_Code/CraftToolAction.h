// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"

class AForgeActor;

/**
 * 
 */
class FIT3094_A2_CODE_API CraftToolAction : public GOAPAction
{
public:
	CraftToolAction();
	~CraftToolAction();

	// Pure virtual functions that child classes MUST implement
	// Whether or not an action has finished executing
	virtual bool IsActionDone() override;
	// Check procedural preconditions at run time. Provide an agent
	bool CheckProceduralPrecondition(AGOAPActor* Agent);
	// Actually perform the action
	// Returns true unless the action can no longer be completed
	// This is called each frame until the action is done
	bool PerformAction(AGOAPActor* Agent);
	// Whether or not the action actually requires something in range
	// Some action can be executed anywhere. Others need specific spots
	bool RequireInRange();

private:
	virtual void Reset();

	// A pointer to the forge. Stored so that we don't waste
	// resources doing constant collision checks. We could also have this
	// linked with world controller for easier access (A1)
	AForgeActor* Forge;

	// How many metal resources have tool crafters gather this action
	int32 StoneResourceCollected;

	// Check if a tool has been created
	bool ToolCrafted;

	// Timer used for determining when to collect resources (Timer based)
	int64 TargetTime;

	// How often timer increment 1 = 1s
	const int64 Timer = 1;
};
