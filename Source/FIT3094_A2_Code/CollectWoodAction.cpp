// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectWoodAction.h"

#include "WoodCutterActor.h"
#include "GOAPActor.h"
#include "TreeActor.h"
#include "Kismet/KismetSystemLibrary.h"

CollectWoodAction::CollectWoodAction()
{
	Reset();
	ActionCost = 2;
}

CollectWoodAction::~CollectWoodAction()
{
}

bool CollectWoodAction::IsActionDone()
{
	if (WoodResourceCollected)
	{
		return true;
	}

	return false;
}

bool CollectWoodAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
	// If wood cutters do not already have trees stored then find some
	if (TreeResourceList.Num() == 0)
	{
		// List of overlaps with other actors we are about to generate
		TArray<AActor*> mOverlaps;
		// We can define actors to ignore. We could ignore this wood cutter
		TArray<AActor*> mIgnores;

		// What objects are we looking for
		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
		objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
		UKismetSystemLibrary::SphereOverlapActors(Agent->GetWorld(), Agent->GetActorLocation(),
			5000.0f, objectTypes, NULL, mIgnores, mOverlaps);

		// For each overlap found
		for (auto actor : mOverlaps)
		{
			// Attempt to cast to a tree resource object
			ATreeActor* TreePointer = Cast<ATreeActor>(actor);
			if (TreePointer)
			{
				// If successful then add it to tree resource list
				TreeResourceList.Add(TreePointer);
			}
		}
	}

	// Find nearest tree resource. Start with null
	ATreeActor* NearestTree = nullptr;
	// For each tree resource available
	for (auto tree : TreeResourceList)
	{
		// If we already have a resource
		if (NearestTree)
		{
			// Check distance from current location to current tree resource and new tree resource
			if (FVector::Dist(tree->GetActorLocation(), Agent->GetActorLocation()) <
				FVector::Dist(NearestTree->GetActorLocation(), Agent->GetActorLocation()))
			{
				// If shorter, have new closest
				NearestTree = tree;
			}
		}
		else
		{
			// If nearest is null
			NearestTree = tree;
		}
	}

	// If nearest is not null
	if (NearestTree)
	{
		Target = NearestTree;
		return true;
	}

	// If got to this point, fail
	return false;
}

bool CollectWoodAction::PerformAction(AGOAPActor* Agent)
{
	// Check if wood cutter have enough health to do this action
	if (AWoodCutterActor* WoodCutter = Cast<AWoodCutterActor>(Agent))
	{
		if (WoodCutter->GetHealth() < WoodCutter->GetMinHealth())
		{
			return false;
		}

		if (WoodCutter->GetToolDurability() == 0)
		{
			return false;
		}
	}
	
	ATreeActor* Tree = Cast<ATreeActor>(Target);
	AWoodCutterActor* WoodCutter = Cast<AWoodCutterActor>(Agent);

	if (!Tree || !WoodCutter)
	{
		return false;
	}

	// Per second decrease wood from tree resource to add to wood cutter
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		Tree->DecreaseWoodResources();
		WoodCutter->NumWoodResources += 1;
		WoodCutter->DecreaseToolDurability();

		if (WoodCutter->NumWoodResources == 50)
		{
			WoodResourceCollected = true;
		}

		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool CollectWoodAction::RequireInRange()
{
	return true;
}

void CollectWoodAction::Reset()
{
	SetInRange(false);
	Target = nullptr;
	WoodResourceCollected = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
