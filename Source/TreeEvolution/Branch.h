// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Leaf.h"
#include "GameFramework/Actor.h"
#include "Branch.generated.h"


const int NOT_PLACED = -1;

UCLASS()
class TREEEVOLUTION_API ABranch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABranch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FVector getPositionOnBranch(float offset);
	FVector getBegin();
	FVector getEnd();
	UPrimitiveComponent* getEndComponent();

	UPROPERTY(EditAnywhere, Category = "Algorithm")
		float rotationChance = .005f;
	UPROPERTY(EditAnywhere, Category = "Algorithm")
		float cost = 0.5;


	float calculateCost();

	void displace(FVector loc, FRotator rot);

	bool mutate();

	int32 placedOn = NOT_PLACED;


private:
	FRandomStream random;
	FVector begin;
	FVector end;
};
