// Fill out your copyright notice in the Description page of Project Settings.


#include "ForgeActor.h"

// Sets default values
AForgeActor::AForgeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AForgeActor::BeginPlay()
{
	Super::BeginPlay();

	// Set collision channel to be Game Trace 1
	VisibleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

// Called every frame
void AForgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int AForgeActor::CraftTool()
{
	int Tool = 0;
	if (MetalResources == 7)
	{
		MetalResources = 0;
		Tool += 1;
		return Tool;
	}

	return Tool;
}