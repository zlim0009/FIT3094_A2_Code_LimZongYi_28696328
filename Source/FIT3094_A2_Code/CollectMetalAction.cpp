// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectMetalAction.h"
#include "GOAPActor.h"
#include "ToolCrafterActor.h"
#include "MineActor.h"
#include "Kismet/KismetSystemLibrary.h"

CollectMetalAction::CollectMetalAction()
{
	Reset();
	ActionCost = 2;
}

CollectMetalAction::~CollectMetalAction()
{
}

bool CollectMetalAction::IsActionDone()
{
	if (MetalResourceCollected)
	{
		return true;
	}

	return false;
}

bool CollectMetalAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
	// If tool crafter do not already have mine stored then find some
	if (MineResourceList.Num() == 0)
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
			// Attempt to cast to a mine resource object
			AMineActor* MinePointer = Cast<AMineActor>(actor);
			if (MinePointer)
			{
				// If successful then add it to stone resource list
				MineResourceList.Add(MinePointer);
			}
		}
	}

	// Find nearest mine resource. Start with null
	AMineActor* NearestMine = nullptr;
	// For each mine resource available
	for (auto mine : MineResourceList)
	{
		// If we already have a resource
		if (NearestMine)
		{
			// Check distance from current location to current mine resource and new stone resource
			if (FVector::Dist(mine->GetActorLocation(), Agent->GetActorLocation()) <
				FVector::Dist(NearestMine->GetActorLocation(), Agent->GetActorLocation()))
			{
				// If shorter, have new closest
				NearestMine = mine;
			}
		}
		else
		{
			// If nearest is null
			NearestMine = mine;
		}
	}

	// If nearest is not null
	if (NearestMine)
	{
		Target = NearestMine;
		return true;
	}

	// If got to this point, fail
	return false;
}

bool CollectMetalAction::PerformAction(AGOAPActor* Agent)
{
	// Check if tool crafter have enough health to do this action
	if (AToolCrafterActor* ToolCrafter = Cast<AToolCrafterActor>(Agent))
	{
		if (ToolCrafter->GetHealth() < ToolCrafter->GetMinHealth())
		{
			return false;
		}
	}
	
	AMineActor* Mine = Cast<AMineActor>(Target);
	AToolCrafterActor* ToolCrafter = Cast<AToolCrafterActor>(Agent);

	if (!Mine || !ToolCrafter)
	{
		return false;
	}

	// Per second decrease stone from stone resource to add to stone mason
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		Mine->DecreaseMetalResources();
		ToolCrafter->NumMetalResources += 1;

		if (ToolCrafter->NumMetalResources == 10)
		{
			MetalResourceCollected = true;
		}

		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool CollectMetalAction::RequireInRange()
{
	return true;
}

void CollectMetalAction::Reset()
{
	SetInRange(false);
	Target = nullptr;
	MetalResourceCollected = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
