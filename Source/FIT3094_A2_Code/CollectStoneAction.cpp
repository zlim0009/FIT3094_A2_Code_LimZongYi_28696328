// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectStoneAction.h"
#include "StoneMasonActor.h"
#include "GOAPActor.h"
#include "StoneActor.h"
#include "Kismet/KismetSystemLibrary.h"

CollectStoneAction::CollectStoneAction()
{
	Reset();
	ActionCost = 2;
}

CollectStoneAction::~CollectStoneAction()
{
}

bool CollectStoneAction::IsActionDone()
{
	if (StoneResourceCollected)
	{
		return true;
	}

	return false;
}

bool CollectStoneAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{

	// If stone masons do not already have stones stored then find some
	if (StoneResourceList.Num() == 0)
	{
		// List of overlaps with other actors we are about to generate
		TArray<AActor*> mOverlaps;
		// We can define actors to ignore. We could ignore this stone mason
		TArray<AActor*> mIgnores;

		// What objects are we looking for
		TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
		objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
		UKismetSystemLibrary::SphereOverlapActors(Agent->GetWorld(), Agent->GetActorLocation(),
			5000.0f, objectTypes, NULL, mIgnores, mOverlaps);

		// For each overlap found
		for (auto actor : mOverlaps)
		{
			// Attempt to cast to a stone resource object
			AStoneActor* StonePointer = Cast<AStoneActor>(actor);
			if (StonePointer)
			{
				// If successful then add it to stone resource list
				StoneResourceList.Add(StonePointer);
			}
		}
	}

	// Find nearest stone resource. Start with null
	AStoneActor* NearestStone = nullptr;
	// For each stone resource available
	for (auto stone : StoneResourceList)
	{
		// If we already have a resource
		if (NearestStone)
		{
			// Check distance from current location to current stone resource and new stone resource
			if (FVector::Dist(stone->GetActorLocation(), Agent->GetActorLocation()) <
				FVector::Dist(NearestStone->GetActorLocation(), Agent->GetActorLocation()))
			{
				// If shorter, have new closest
				NearestStone = stone;
			}
		}
		else
		{
			// If nearest is null
			NearestStone = stone;
		}
	}

	// If nearest is not null
	if (NearestStone)
	{
		Target = NearestStone;
		return true;
	}

	// If got to this point, fail
	return false;
}

bool CollectStoneAction::PerformAction(AGOAPActor* Agent)
{
	// Check if stone masons have enough health to do this action
	if (AStoneMasonActor* StoneMason = Cast<AStoneMasonActor>(Agent))
	{
		if (StoneMason->GetHealth() < StoneMason->GetMinHealth())
		{
			return false;
		}

		if (StoneMason->GetToolDurability() == 0)
		{
			return false;
		}
	}

	AStoneActor* Stone = Cast<AStoneActor>(Target);
	AStoneMasonActor* StoneMason = Cast<AStoneMasonActor>(Agent);

	if (!Stone || !StoneMason)
	{
		return false;
	}

	// Per second decrease stone from stone resource to add to stone mason
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		Stone->DecreaseStoneResources();
		StoneMason->NumStoneResources += 1;
		StoneMason->DecreaseToolDurability();

		if (StoneMason->NumStoneResources == 20)
		{
			StoneResourceCollected = true;
		}
		
		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool CollectStoneAction::RequireInRange()
{
	return true;
}

void CollectStoneAction::Reset()
{
	SetInRange(false);
	Target = nullptr;
	StoneResourceCollected = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
