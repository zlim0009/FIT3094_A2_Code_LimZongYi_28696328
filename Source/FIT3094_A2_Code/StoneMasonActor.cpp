// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneMasonActor.h"

#include "CollectStoneAction.h"
#include "DropStoneAction.h"
#include "GetFoodAction.h"
#include "GetToolAction.h"
#include "UObject/ConstructorHelpers.h"


AStoneMasonActor::AStoneMasonActor() : AGOAPActor()
{
	// Stuff for configuring materials and static mesh components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	// Attempt to load from file
	ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMeshInstance(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));

	// If cylinder was able to be loaded set it to the static mesh. Do the same for the material
	if (CylinderMeshInstance.Succeeded())
	{
		VisibleComponent->SetStaticMesh(CylinderMeshInstance.Object);
	}

	Health = MaxHealth;
	NumStoneResources = 0;
	
	ToolDurability = 0;
}

void AStoneMasonActor::BeginPlay()
{
	Super::BeginPlay();

	// Set a timer for every two seconds and call the decrease health function
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AStoneMasonActor::DecreaseHealth, 2.0f, true, 2.0f);

	// Assign the actions to the actor
	CollectStoneAction* CollectStone = new CollectStoneAction();
	CollectStone->AddPrecondition("HasStoneResource", false);
	CollectStone->AddEffect("HasStoneResource", true);
	AvailableActions.Add(CollectStone);

	DropStoneAction* DropStone = new DropStoneAction();
	DropStone->AddPrecondition("DropStoneResource", false);
	DropStone->AddEffect("DropStoneResource", true);
	AvailableActions.Add(DropStone);

	GetFoodAction* GetFood = new GetFoodAction();
	GetFood->AddPrecondition("GotFood", false);
	GetFood->AddEffect("GotFood", true);
	AvailableActions.Add(GetFood);

	GetToolAction* GetTool = new GetToolAction();
	GetTool->AddPrecondition("GotTool", false);
	GetTool->AddEffect("GotTool", true);
	AvailableActions.Add(GetTool);
}

void AStoneMasonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStoneMasonActor::DecreaseHealth()
{
	// Decrease health by one and if 0 then destroy object
	Health--;

	if (Health <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}
}

TMap<FString, bool> AStoneMasonActor::GetWorldState()
{
	TMap<FString, bool> WorldState = Super::GetWorldState();

	WorldState.Add("HasStoneResource", NumStoneResources == 20);
	WorldState.Add("DropStoneResource", NumStoneResources == 0);
	WorldState.Add("GotFood", Health > MinHealth);
	WorldState.Add("GotTool", ToolDurability > 0);

	return WorldState;
}

TMap<FString, bool> AStoneMasonActor::CreateGoalState()
{
	TMap<FString, bool> GoalState;

	if (Health < MinHealth)
	{
		GoalState.Add("GotFood", true);
	} else
	{
		if (ToolDurability == 0)
		{
			GoalState.Add("GotTool", true);
		} else if (NumStoneResources != 20)
		{
			GoalState.Add("HasStoneResource", true);

		} else if (NumStoneResources != 0)
		{
			GoalState.Add("DropStoneResource", true);
		}
	}

	return GoalState;
}