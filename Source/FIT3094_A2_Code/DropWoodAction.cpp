// Fill out your copyright notice in the Description page of Project Settings.


#include "DropWoodAction.h"

#include "GOAPActor.h"
#include "VillageCentreActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WoodCutterActor.h"

DropWoodAction::DropWoodAction()
{
	Reset();
	ActionCost = 2;
}

DropWoodAction::~DropWoodAction()
{
}

bool DropWoodAction::IsActionDone()
{
	if (WoodResourceDropped)
	{
		return true;
	}

	return false;
}

bool DropWoodAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
	if (!VillageCentre)
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
			// Attempt to cast to a village centre
			AVillageCentreActor* VillageCentrePointer = Cast<AVillageCentreActor>(actor);
			if (VillageCentrePointer)
			{
				VillageCentre = VillageCentrePointer;
				Target = VillageCentre;
				return true;
			}
		}
	} else
	{
		Target = VillageCentre;
		return true;
	}
	

	// If got to this point, fail
	return false;
}

bool DropWoodAction::PerformAction(AGOAPActor* Agent)
{
	// Check if wood cutter have enough health to do this action
	if (AWoodCutterActor* WoodCutter = Cast<AWoodCutterActor>(Agent))
	{
		if (WoodCutter->GetHealth() < WoodCutter->GetMinHealth())
		{
			return false;
		}
	}

	AWoodCutterActor* WoodCutter = Cast<AWoodCutterActor>(Agent);

	if (!VillageCentre || !WoodCutter)
	{
		return false;
	}

	// Per second drop wood from wood cutter to add to village centre
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		WoodCutter->NumWoodResources -= 1;
		VillageCentre->IncreaseWoodResources();

		if (WoodCutter->NumWoodResources == 0)
		{
			WoodResourceDropped = true;
		}
		
		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool DropWoodAction::RequireInRange()
{
	return true;
}

void DropWoodAction::Reset()
{
	SetInRange(false);
	VillageCentre = nullptr;
	WoodResourceDropped = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
