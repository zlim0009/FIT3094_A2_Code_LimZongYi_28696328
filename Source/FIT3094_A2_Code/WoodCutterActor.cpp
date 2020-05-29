// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodCutterActor.h"

#include "CollectWoodAction.h"
#include "DropWoodAction.h"
#include "GetFoodAction.h"
#include "GetToolAction.h"
#include "UObject/ConstructorHelpers.h"

AWoodCutterActor::AWoodCutterActor() : AGOAPActor()
{
	// Stuff for configuring materials and static mesh components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	// Attempt to load from file
	ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMeshInstance(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));

	// If cone was able to be loaded set it to the static mesh. Do the same for the material
	if (ConeMeshInstance.Succeeded())
	{
		VisibleComponent->SetStaticMesh(ConeMeshInstance.Object);
	}

	Health = MaxHealth;
	NumWoodResources = 0;
	
	ToolDurability = 0;
}

void AWoodCutterActor::BeginPlay()
{
	Super::BeginPlay();

	// Set a timer for every two seconds and call the decrease health function
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWoodCutterActor::DecreaseHealth, 2.0f, true, 2.0f);
	
	// Assign the actions to the actor
	CollectWoodAction* CollectWood = new CollectWoodAction();
	CollectWood->AddPrecondition("HasWoodResource", false);
	CollectWood->AddEffect("HasWoodResource", true);
	AvailableActions.Add(CollectWood);

	DropWoodAction* DropWood = new DropWoodAction();
	DropWood->AddPrecondition("DropWoodResource", false);
	DropWood->AddEffect("DropWoodResource", true);
	AvailableActions.Add(DropWood);

	GetFoodAction* GetFood = new GetFoodAction();
	GetFood->AddPrecondition("GotFood", false);
	GetFood->AddEffect("GotFood", true);
	AvailableActions.Add(GetFood);

	GetToolAction* GetTool = new GetToolAction();
	GetTool->AddPrecondition("GotTool", false);
	GetTool->AddEffect("GotTool", true);
	AvailableActions.Add(GetTool);
}

void AWoodCutterActor::DecreaseHealth()
{
	// Decrease health by one and if 0 then destroy object
	Health--;

	if (Health <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}
}

void AWoodCutterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TMap<FString, bool> AWoodCutterActor::GetWorldState()
{
	TMap<FString, bool> WorldState = Super::GetWorldState();

	WorldState.Add("HasWoodResource", NumWoodResources == 50);
	WorldState.Add("DropWoodResource", NumWoodResources == 0);
	WorldState.Add("GotFood", Health > MinHealth);
	WorldState.Add("GotTool", ToolDurability > 0);
	
	return WorldState;
}

TMap<FString, bool> AWoodCutterActor::CreateGoalState()
{
	TMap<FString, bool> GoalState;

	if (Health < MinHealth)
	{
		GoalState.Add("GotFood", true);
	}
	else
	{
		if (ToolDurability == 0)
		{
			GoalState.Add("GotTool", true);
		} else if (NumWoodResources != 50)
		{
			GoalState.Add("HasWoodResource", true);
		} else if (NumWoodResources != 0)
		{
			GoalState.Add("DropWoodResource", true);
		}
	}
	
	return GoalState;
}