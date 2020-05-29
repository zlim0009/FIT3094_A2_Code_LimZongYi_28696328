// Fill out your copyright notice in the Description page of Project Settings.


#include "VillageCentreActor.h"

// Sets default values
AVillageCentreActor::AVillageCentreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AVillageCentreActor::BeginPlay()
{
	Super::BeginPlay();

	// Set collision channel to be Game Trace 1
	VisibleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

// Called every frame
void AVillageCentreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AVillageCentreActor::CheckForWood()
{
	if (WoodResources > 0)
	{
		return true;
	}

	return false;
}

bool AVillageCentreActor::CheckForStone()
{
	if (StoneResources > 0)
	{
		return true;
	}

	return false;
}

bool AVillageCentreActor::CheckForTools()
{
	if (Tools > 0)
	{
		return true;
	}

	return false;
}