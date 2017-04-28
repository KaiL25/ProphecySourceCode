// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "SphereInsertion.h"
#include "SecretDoor.h"
#include "ProphecyCharacter.h"
#include "Engine.h"

ASphereInsertion::ASphereInsertion()
{
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
}

void ASphereInsertion::BeginPlay()
{
	Sphere->SetVisibility(false);
	for (TActorIterator<ASecretDoor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("HallwaySecretDoor"))
		{
			HallwayDoor = *ActorItr;
		}
	}
}

void ASphereInsertion::InteractWithObject()
{
	if (CurrentPlayer->IsCollected(CollectableIndex))
	{
		Sphere->SetVisibility(true);
		HallwayDoor->OpenSecretDoor();
	}
}

