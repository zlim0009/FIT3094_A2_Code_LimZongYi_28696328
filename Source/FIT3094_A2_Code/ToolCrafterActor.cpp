// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolCrafterActor.h"
#include "CollectMetalAction.h"
#include "CraftToolAction.h"
#include "DropToolAction.h"
#include "GetFoodAction.h"
#include "UObject/ConstructorHelpers.h"

AToolCrafterActor::AToolCrafterActor() : AGOAPActor()
{
	// Stuff for configuring materials and static mesh components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	// Attempt to load from file
	ConstructorHelpers::FObjectFinder<UStaticMesh> TorusMeshInstance(TEXT("/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus"));

	// If torus was able to be loaded set it to the static mesh. Do the same for the material
	if (TorusMeshInstance.Succeeded())
	{
		VisibleComponent->SetStaticMesh(TorusMeshInstance.Object);
	}

	Health = MaxHealth;
	NumMetalResources = 0;
	NumTools = 0;
}

void AToolCrafterActor::BeginPlay()
{
	Super::BeginPlay();

	// Set a timer for every two seconds and call the decrease health function
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AToolCrafterActor::DecreaseHealth, 2.0f, true, 2.0f);

	// Assign the actions to the actor
	CollectMetalAction* CollectMetal = new CollectMetalAction();
	CollectMetal->AddPrecondition("HasMetalResource", false);
	CollectMetal->AddEffect("HasMetalResource", true);
	AvailableActions.Add(CollectMetal);

	CraftToolAction* CraftTool = new CraftToolAction();
	CraftTool->AddPrecondition("HasCraftTool", false);
	CraftTool->AddEffect("HasCraftTool", true);
	AvailableActions.Add(CraftTool);

	DropToolAction* DropTool = new DropToolAction();
	DropTool->AddPrecondition("DropTool", false);
	DropTool->AddEffect("DropTool", true);
	AvailableActions.Add(DropTool);

	GetFoodAction* GetFood = new GetFoodAction();
	GetFood->AddPrecondition("GotFood", false);
	GetFood->AddEffect("GotFood", true);
	AvailableActions.Add(GetFood);
}

void AToolCrafterActor::DecreaseHealth()
{
	// Decrease health by one and if 0 then destroy object
	Health--;

	if (Health <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}
}

void AToolCrafterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TMap<FString, bool> AToolCrafterActor::GetWorldState()
{
	TMap<FString, bool> WorldState = Super::GetWorldState();

	WorldState.Add("HasMetalResource", NumMetalResources == 10);
	WorldState.Add("HasCraftTool", NumTools == 1);
	WorldState.Add("DropTool", NumTools == 0);
	WorldState.Add("GotFood", Health > MinHealth);
	
	return WorldState;
}

TMap<FString, bool> AToolCrafterActor::CreateGoalState()
{
	TMap<FString, bool> GoalState;

	if (Health < MinHealth)
	{
		GoalState.Add("GotFood", true);
	} else
	{
		if (NumMetalResources != 10 && NumTools != 1)
		{
			GoalState.Add("HasMetalResource", true);
		} else if (NumTools != 1)
		{
			GoalState.Add("HasCraftTool", true);
		} else if (NumTools != 0)
		{
			GoalState.Add("DropTool", true);
		}
	}
	
	return GoalState;
}