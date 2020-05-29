// Fill out your copyright notice in the Description page of Project Settings.


#include "GetFoodAction.h"
#include "GOAPActor.h"
#include "FoodActor.h"
#include "WoodCutterActor.h"
#include "StoneMasonActor.h"
#include "BuilderActor.h"
#include "ToolCrafterActor.h"
#include "Kismet/KismetSystemLibrary.h"

GetFoodAction::GetFoodAction()
{
	Reset();
	ActionCost = 1;
}

GetFoodAction::~GetFoodAction()
{
}

bool GetFoodAction::IsActionDone()
{
	if (IsHealthCollected)
	{
		return true;
	}

	return false;
}

bool GetFoodAction::CheckProceduralPrecondition(AGOAPActor* Agent)
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
		AFoodActor* StonePointer = Cast<AFoodActor>(actor);
		if (StonePointer)
		{
			// If successful then add it to stone resource list
			FoodList.Add(StonePointer);
		}
	}

	// Find nearest food. Start with null
	AFoodActor* NearestFood = nullptr;
	// For each food available
	for (auto food : FoodList)
	{
		// If we already have a resource
		if (NearestFood)
		{
			// Check distance from current location to current food and new food
			if (FVector::Dist(food->GetActorLocation(), Agent->GetActorLocation()) <
				FVector::Dist(NearestFood->GetActorLocation(), Agent->GetActorLocation()))
			{
				// If shorter, have new closest
				NearestFood = food;
			}
		}
		else
		{
			// If nearest is null
			NearestFood = food;
		}
	}

	// If nearest is not null
	if (NearestFood)
	{
		Target = NearestFood;
		return true;
	}

	// If got to this point, fail
	return false;
}

bool GetFoodAction::PerformAction(AGOAPActor* Agent)
{
	AFoodActor* Food = Cast<AFoodActor>(Target);
	AGOAPActor* Actor = Cast<AGOAPActor>(Agent);

	if (!Food || !Actor)
	{
		return false;
	}

	// At target time, destroy food and add health to actor
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		if (AWoodCutterActor* WoodCutter = Cast<AWoodCutterActor>(Actor))
		{
			WoodCutter->Heal();
		}
		else if (AStoneMasonActor* StoneMason = Cast<AStoneMasonActor>(Actor))
		{
			StoneMason->Heal();
		}
		else if (ABuilderActor* Builder = Cast<ABuilderActor>(Actor))
		{
			Builder->Heal();
		}
		else if (AToolCrafterActor* ToolCrafter = Cast<AToolCrafterActor>(Actor))
		{
			ToolCrafter->Heal();
		}

		IsHealthCollected = true;
	}

	return true;
}

bool GetFoodAction::RequireInRange()
{
	return true;
}

void GetFoodAction::Reset()
{
	SetInRange(false);
	FoodList.Empty();
	Target = nullptr;
	IsHealthCollected = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}
