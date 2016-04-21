// Fill out your copyright notice in the Description page of Project Settings.

#include "TreeEvolution.h"
#include "Branch.h"


// Sets default values
ABranch::ABranch()
{

	PrimaryActorTick.bCanEverTick = false;

	random.GenerateNewSeed();
}

// Called when the game starts or when spawned
void ABranch::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABranch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FVector ABranch::getPositionOnBranch(float offset) {

	TArray<UPrimitiveComponent*> comps;
	GetComponents(comps);
	FVector begin;
	FVector end;

	// this is a strange way to find the end and starting components, should probably be refactored sometime...
	for (auto Itr(comps.CreateIterator()); Itr; ++Itr)
	{
		if ((*Itr)->GetName() == "start") {
			begin = (*Itr)->GetComponentLocation();
		}
		else if ((*Itr)->GetName() == "end")
		{
			end = (*Itr)->GetComponentLocation();

		}
	}

	return begin + (end - begin)*offset;
}

FVector ABranch::getBegin() {
	TArray<UPrimitiveComponent*> comps;
	GetComponents(comps);
	for (auto Itr(comps.CreateIterator()); Itr; ++Itr)
	{
		if ((*Itr)->GetName() == "start") 
			return (*Itr)->GetComponentLocation();
		
	}

	throw - 1;
}

FVector ABranch::getEnd() {
	TArray<UPrimitiveComponent*> comps;
	GetComponents(comps);
	for (auto Itr(comps.CreateIterator()); Itr; ++Itr)
	{
		if ((*Itr)->GetName() == "end")
			return (*Itr)->GetComponentLocation();

	}

	throw - 1;
}

UPrimitiveComponent* ABranch::getEndComponent() {
	TArray<UPrimitiveComponent*> comps;
	GetComponents(comps);
	for (auto Itr(comps.CreateIterator()); Itr; ++Itr)
	{
		if ((*Itr)->GetName() == "end")
			return (*Itr);

	}

	throw -1;

}



float ABranch::calculateCost() {
	return cost;
}

bool ABranch::overlapsProps() {
	TArray< AActor * > OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* a : OverlappingActors) {
		ABranch* actor = Cast<ABranch>(a);
		if (!a) {
			// prop was not a branch, this means there is an overlap
			return true;
		}
	}

	return false;
}


void ABranch::displace(FVector loc, FRotator rot) {
	SetActorLocation(loc);
	SetActorRotation(rot);
}

bool ABranch::mutate() {
	if (random.FRand() < rotationChance) {
		AddActorLocalRotation(FQuat(FRotator(random.FRand() * 30 - 15, random.FRand() * 30 - 15, random.FRand() * 30 - 15)));
		return true;
	}
	return false;
}