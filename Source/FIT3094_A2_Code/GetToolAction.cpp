// Fill out your copyright notice in the Description page of Project Settings.


#include "GetToolAction.h"
#include "GOAPActor.h"
#include "VillageCentreActor.h"
#include "WoodCutterActor.h"
#include "StoneMasonActor.h"
#include "Kismet/KismetSystemLibrary.h"

GetToolAction::GetToolAction()
{
	Reset();
}

GetToolAction::~GetToolAction()
{
}

bool GetToolAction::IsActionDone()
{
	if (ToolCollected)
	{
		return true;
	}

	return false;
}

bool GetToolAction::CheckProceduralPrecondition(AGOAPActor* Agent)
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

bool GetToolAction::PerformAction(AGOAPActor* Agent)
{
	if (AWoodCutterActor* WoodCutter = Cast<AWoodCutterActor>(Agent))
	{
		if (WoodCutter->GetHealth() < WoodCutter->GetMinHealth())
		{
			return false;
		}
	}
	else if (AStoneMasonActor* StoneMason = Cast<AStoneMasonActor>(Agent))
	{
		if (StoneMason->GetHealth() < StoneMason->GetMinHealth())
		{
			return false;
		}
	}

	AGOAPActor* Actor = Cast<AGOAPActor>(Agent);

	if (!VillageCentre || !Actor)
	{
		return false;
	}

	// Check if there are tools in the village centre
	if (!VillageCentre->CheckForTools())
	{
		return false;
	}

	// At target time, destroy food and add health to actor
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		if (AWoodCutterActor* WoodCutter = Cast<AWoodCutterActor>(Actor))
		{
			WoodCutter->ResetToolDurability();
		}
		else if (AStoneMasonActor* StoneMason = Cast<AStoneMasonActor>(Actor))
		{
			StoneMason->ResetToolDurability();
		}

		VillageCentre->DecreaseTools();
		ToolCollected = true;
	}

	return true;
}

bool GetToolAction::RequireInRange()
{
	return true;
}

void GetToolAction::Reset()
{
	SetInRange(false);
	VillageCentre = nullptr;
	ToolCollected = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
