// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectWoodAndStoneAction.h"
#include "GOAPActor.h"
#include "VillageCentreActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BuilderActor.h"

CollectWoodAndStoneAction::CollectWoodAndStoneAction()
{
	Reset();
	ActionCost = 2;
}

CollectWoodAndStoneAction::~CollectWoodAndStoneAction()
{
}

bool CollectWoodAndStoneAction::IsActionDone()
{
	if (WoodAndStoneResourceCollected)
	{
		return true;
	}

	return false;
}

bool CollectWoodAndStoneAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
	if (!VillageCentre)
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

bool CollectWoodAndStoneAction::PerformAction(AGOAPActor* Agent)
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

	if (!VillageCentre || !Builder)
	{
		return false;
	}

	// Check if there are resources in the village centre
	if (!VillageCentre->CheckForWood() || !VillageCentre->CheckForStone())
	{
		return false;
	}

	// Per second collect wood and stone from village centre to add to builder
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		if (Builder->NumStoneResources < 5)
		{
			Builder->NumWoodResources += 1;
			VillageCentre->DecreaseWoodResources();

			Builder->NumStoneResources += 1;
			VillageCentre->DecreaseStoneResources();
		} else
		{
			Builder->NumWoodResources += 1;
			VillageCentre->DecreaseWoodResources();
		}

		if (Builder->NumWoodResources == 10 && Builder->NumStoneResources == 5)
		{
			WoodAndStoneResourceCollected = true;
		}

		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool CollectWoodAndStoneAction::RequireInRange()
{
	return true;
}

void CollectWoodAndStoneAction::Reset()
{
	SetInRange(false);
	VillageCentre = nullptr;
	WoodAndStoneResourceCollected = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
