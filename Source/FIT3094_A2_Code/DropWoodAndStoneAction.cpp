// Fill out your copyright notice in the Description page of Project Settings.


#include "DropWoodAndStoneAction.h"

#include "GOAPActor.h"
#include "BuildingActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BuilderActor.h"

DropWoodAndStoneAction::DropWoodAndStoneAction()
{
	Reset();
	ActionCost = 2;
}

DropWoodAndStoneAction::~DropWoodAndStoneAction()
{
}

bool DropWoodAndStoneAction::IsActionDone()
{
	if (WoodAndStoneDropped)
	{
		return true;
	}

	return false;
}

bool DropWoodAndStoneAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
	if (!Building)
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
			// Attempt to cast to a village centre
			ABuildingActor* BuildingPointer = Cast<ABuildingActor>(actor);
			if (BuildingPointer)
			{
				Building = BuildingPointer;
				Target = Building;
				return true;
			}
		}
	}
	else
	{
		Target = Building;
		return true;
	}

	// If got to this point, fail
	return false;
}

bool DropWoodAndStoneAction::PerformAction(AGOAPActor* Agent)
{
	// Check if builder have enough health to do this action
	if (ABuilderActor* Builder = Cast<ABuilderActor>(Agent))
	{
		if (Builder->GetHealth() < Builder->GetMinHealth())
		{
			return false;
		}
	}

	ABuilderActor* Builder = Cast<ABuilderActor>(Agent);

	if (!Building || !Builder)
	{
		return false;
	}

	// Per second collect stone from village centre to add to builder
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		if (Builder->NumStoneResources != 0)
		{
			Builder->NumWoodResources -= 1;
			Building->IncreaseWoodResources();

			Builder->NumStoneResources -= 1;
			Building->IncreaseStoneResources();
		}
		else
		{
			Builder->NumWoodResources -= 1;
			Building->IncreaseWoodResources();
		}

		if (Builder->NumWoodResources == 0 && Builder->NumStoneResources == 0)
		{
			WoodAndStoneDropped = true;
		}
		
		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool DropWoodAndStoneAction::RequireInRange()
{
	return true;
}

void DropWoodAndStoneAction::Reset()
{
	SetInRange(false);
	Building = nullptr;
	WoodAndStoneDropped = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
