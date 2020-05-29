// Fill out your copyright notice in the Description page of Project Settings.


#include "DropStoneAction.h"

#include "GOAPActor.h"
#include "VillageCentreActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "StoneMasonActor.h"

DropStoneAction::DropStoneAction()
{
	Reset();
	ActionCost = 2;
}

DropStoneAction::~DropStoneAction()
{
}

bool DropStoneAction::IsActionDone()
{
	if (StoneResourceDropped)
	{
		return true;
	}

	return false;
}

bool DropStoneAction::CheckProceduralPrecondition(AGOAPActor* Agent)
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

bool DropStoneAction::PerformAction(AGOAPActor* Agent)
{
	// Check if stone masons have enough health to do this action
	if (AStoneMasonActor* StoneMason = Cast<AStoneMasonActor>(Agent))
	{
		if (StoneMason->GetHealth() < StoneMason->GetMinHealth())
		{
			return false;
		}
	}

	AStoneMasonActor* StoneMason = Cast<AStoneMasonActor>(Agent);

	if (!VillageCentre || !StoneMason)
	{
		return false;
	}

	// Per second drop stone from stone mason to add to village centre
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		StoneMason->NumStoneResources -= 1;
		VillageCentre->IncreaseStoneResources();

		if (StoneMason->NumStoneResources == 0)
		{
			StoneResourceDropped = true;
		}
		
		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool DropStoneAction::RequireInRange()
{
	return true;
}

void DropStoneAction::Reset()
{
	SetInRange(false);
	VillageCentre = nullptr;
	StoneResourceDropped = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
