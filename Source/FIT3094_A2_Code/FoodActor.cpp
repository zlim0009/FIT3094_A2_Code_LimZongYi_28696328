// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodActor.h"

#include "GOAPActor.h"

// Sets default values
AFoodActor::AFoodActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Component"));
	VisibleComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetupAttachment(VisibleComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFoodActor::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AFoodActor::BeginPlay()
{
	Super::BeginPlay();

	// Set collision channel to be Game Trace 1
	VisibleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

// Called every frame
void AFoodActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if OtherActor is a GOAPActor
	if (AGOAPActor* Actor = Cast<AGOAPActor>(OtherActor))
	{
		// Get the current action of the actor and check for its target
		if(Actor->GetCurrentAction()->Target == this)
		{
			// If the food is the actor's target, destroy target
			Destroy();
		}
	}
}