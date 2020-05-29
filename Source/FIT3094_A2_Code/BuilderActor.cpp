// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderActor.h"

#include "CollectWoodAndStoneAction.h"
#include "DropWoodAndStoneAction.h"
#include "GetFoodAction.h"
#include "UObject/ConstructorHelpers.h"


ABuilderActor::ABuilderActor() : AGOAPActor()
{
	// Stuff for configuring materials and static mesh components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(RootComponent);

	// Attempt to load from file
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshInstance(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	// If sphere was able to be loaded set it to the static mesh. Do the same for the material
	if (SphereMeshInstance.Succeeded())
	{
		VisibleComponent->SetStaticMesh(SphereMeshInstance.Object);
	}

	Health = MaxHealth;
	NumWoodResources = 0;
	NumStoneResources = 0;
}

void ABuilderActor::BeginPlay()
{
	Super::BeginPlay();

	// Set a timer for every two seconds and call the decrease health function
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABuilderActor::DecreaseHealth, 2.0f, true, 2.0f);

	// Assign the actions to the actor
	CollectWoodAndStoneAction* CollectWoodAndStone = new CollectWoodAndStoneAction();
	CollectWoodAndStone->AddPrecondition("HasWoodAndStoneResource", false);
	CollectWoodAndStone->AddEffect("HasWoodAndStoneResource", true);
	AvailableActions.Add(CollectWoodAndStone);

	DropWoodAndStoneAction* DropWoodAndStone = new DropWoodAndStoneAction();
	DropWoodAndStone->AddPrecondition("DropWoodAndStoneResource", false);
	DropWoodAndStone->AddEffect("DropWoodAndStoneResource", true);
	AvailableActions.Add(DropWoodAndStone);

	GetFoodAction* GetFood = new GetFoodAction();
	GetFood->AddPrecondition("GotFood", false);
	GetFood->AddEffect("GotFood", true);
	AvailableActions.Add(GetFood);
}

void ABuilderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilderActor::DecreaseHealth()
{
	// Decrease health by one and if 0 then destroy object
	Health--;

	if (Health <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}
}

TMap<FString, bool> ABuilderActor::GetWorldState()
{
	TMap<FString, bool> WorldState = Super::GetWorldState();

	WorldState.Add("HasWoodAndStoneResource", NumWoodResources == 10 && NumStoneResources == 5);
	WorldState.Add("DropWoodAndStoneResource", NumWoodResources == 0 && NumStoneResources == 0);
	WorldState.Add("GotFood", Health > MinHealth);
	
	return WorldState;
}

TMap<FString, bool> ABuilderActor::CreateGoalState()
{
	TMap<FString, bool> GoalState;

	if (Health < MinHealth)
	{
		GoalState.Add("GotFood", true);
	}
	else
	{
		if (NumWoodResources != 10 || NumStoneResources != 5)
		{
			GoalState.Add("HasWoodAndStoneResource", true);
		} else if (NumWoodResources != 0 || NumStoneResources != 0)
		{
			GoalState.Add("DropWoodAndStoneResource", true);
		}
	}
	
	return GoalState;
}