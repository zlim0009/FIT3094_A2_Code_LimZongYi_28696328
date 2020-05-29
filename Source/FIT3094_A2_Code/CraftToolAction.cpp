// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftToolAction.h"

#include "GOAPActor.h"
#include "ForgeActor.h"
#include "ToolCrafterActor.h"
#include "Kismet/KismetSystemLibrary.h"

CraftToolAction::CraftToolAction()
{
	Reset();
	ActionCost = 2;
}

CraftToolAction::~CraftToolAction()
{
}

bool CraftToolAction::IsActionDone()
{
	if (ToolCrafted)
	{
		return true;
	}

	return false;
}

bool CraftToolAction::CheckProceduralPrecondition(AGOAPActor* Agent)
{
	if (!Forge)
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
			AForgeActor* ForgePointer = Cast<AForgeActor>(actor);
			if (ForgePointer)
			{
				Forge = ForgePointer;
				Target = Forge;
				return true;
			}
		}
	}
	else
	{
		Target = Forge;
		return true;
	}


	// If got to this point, fail
	return false;
}

bool CraftToolAction::PerformAction(AGOAPActor* Agent)
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

	if (!Forge || !ToolCrafter)
	{
		return false;
	}

	// Per second add metal to forge and add tool if a tool is ready
	if (FDateTime::UtcNow().ToUnixTimestamp() > TargetTime)
	{
		ToolCrafter->NumMetalResources -= 1;
		Forge->IncreaseMetalResources();
		ToolCrafter->NumTools += Forge->CraftTool();

		if (ToolCrafter->NumTools > 0)
		{
			ToolCrafted = true;
		}
		
		TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
	}

	return true;
}

bool CraftToolAction::RequireInRange()
{
	return true;
}

void CraftToolAction::Reset()
{
	SetInRange(false);
	Forge = nullptr;
	ToolCrafted = false;
	TargetTime = FDateTime::UtcNow().ToUnixTimestamp() + Timer;
}