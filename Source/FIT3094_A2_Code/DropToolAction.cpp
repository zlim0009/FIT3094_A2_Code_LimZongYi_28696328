// Fill out your copyright notice in the Description page of Project Settings.


#include "DropToolAction.h"

#include "GOAPActor.h"
#include "VillageCentreActor.h"
#include "ToolCrafterActor.h"
#include "Kismet/KismetSystemLibrary.h"

DropToolAction::DropToolAction()
{
	Reset();
	ActionCost = 2;
}

DropToolAction::~DropToolAction()
{
}

bool DropToolAction::IsActionDone()
{
	if (ToolsDropped)
	{
		return true;
	}

	return false;
}

bool DropToolAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
	if (!VillageCentre)
	{
		// List of overlaps with other actors we are about to generate
		TArray<AActor*> mOverlaps;
		// We can define actors to ignore. We could ignore this tool crafter
		TArray<AActor*> mIgnores;

		// What objects are we looking for
		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
		objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
		UKismetSystemLibrary::SphereOverlapActors(Agent->GetWorld(), Agent->GetActorLocation(),
			5000.0f, objectTypes, NULL, mIgnores, mOverlaps);

		// For each overlap found
		for (auto actor : mOverlaps)
		{
			// Attempt to cast to a village centre
			AVillageCentreActor* VillageCentrePointer = Cast<AVillageCentreActor>(actor);
			if (VillageCentrePointer)
			{
				VillageCentre = VillageCentrePointer;
				Target = VillageCentre;
				return true;
			}
		}
	}
	else
	{
		Target = VillageCentre;
		return true;
	}


	// If got to this point, fail
	return false;
}

bool DropToolAction::PerformAction(AGOAPActor* Agent)
{
	// Check if tool crafter have enough health to do this action
	if (AToolCrafterActor* ToolCrafter = Cast<AToolCrafterActor>(Agent))
	{
		if (ToolCrafter->GetHealth() < ToolCrafter->GetMinHealth())
		{
			return false;
		}
	}

	AToolCrafterActor* ToolCrafter = Cast<AToolCrafterActor>(Agent);

	if (!VillageCentre || !ToolCrafter)
	{
		return false;
	}

	// Per second drop metal from tool crafter to add to village centre
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		ToolCrafter->NumTools -= 1;
		VillageCentre->IncreaseTools();

		if (ToolCrafter->NumTools == 0)
		{
			ToolsDropped = true;
		}

		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool DropToolAction::RequireInRange()
{
	return true;
}

void DropToolAction::Reset()
{
	SetInRange(false);
	VillageCentre = nullptr;
	ToolsDropped = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
