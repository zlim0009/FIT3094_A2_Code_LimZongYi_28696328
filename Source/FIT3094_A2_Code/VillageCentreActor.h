// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "VillageCentreActor.generated.h"

UCLASS()
class FIT3094_A2_CODE_API AVillageCentreActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere, Category="Resources")
		int StoneResources = 0;
	UPROPERTY(EditAnywhere, Category = "Resources")
		int WoodResources = 0;
	UPROPERTY(EditAnywhere, Category = "Resources")
		int MetalResources = 0;
	UPROPERTY(EditAnywhere, Category = "Resources")
		int Tools = 0;
	
public:	
	// Sets default values for this actor's properties
	AVillageCentreActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called to increase wood resources;
	void IncreaseWoodResources() { WoodResources++; }
	//Called to decrease wood resources;
	void DecreaseWoodResources() { WoodResources--; }
	//Called to increase stone resources;
	void IncreaseStoneResources() { StoneResources++; }
	//Called to decrease stone resources;
	void DecreaseStoneResources() { StoneResources--; }
	//Called to increase tools;
	void IncreaseTools() { Tools++; }
	//Called to decrease tools;
	void DecreaseTools() { Tools--; }

	// Called to check if there are wood resources in the village centre
	bool CheckForWood();
	// Called to check if there are stone resources in the village centre
	bool CheckForStone();
	// Called to check if there are tools in the village centre
	bool CheckForTools();
};