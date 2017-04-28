// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "GobletPedestal.h"
#include "ProphecyCharacter.h"
#include "SecretDoor.h"
#include "Engine.h"



AGobletPedestal::AGobletPedestal()
{
	Goblet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Goblet"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));
}

void AGobletPedestal::BeginPlay()
{
	Goblet->SetVisibility(false);
	Water->SetVisibility(false);

	for (TActorIterator<ASecretDoor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("AltarRoomSecretDoor"))
		{
			AltarRoomDoor = *ActorItr;
		}
	}
}

void AGobletPedestal::InteractWithObject()
{
	/*If the player interacts with the pedestal without having the goblet.*/
	if (!CurrentPlayer->IsCollected(CollectableIndex))
	{
		CurrentPlayer->AddTextToUI(gobletPlacementMessage);
		CurrentPlayer->SetClue(gobletPlacementClue);
	}

	else if (CurrentPlayer->IsCollected(CollectableIndex) && !CurrentPlayer->GetFilledWithWater())
	{
		CurrentPlayer->AddTextToUI(gobletContentMessage);
		CurrentPlayer->SetClue(gobletContentClue);
	}

	else if (CurrentPlayer->GetFilledWithWater() && CurrentPlayer->IsCollected(CollectableIndex))
	{
		Goblet->SetVisibility(true);
		Water->SetVisibility(true);
		AltarRoomDoor->OpenSecretDoor();
		CurrentPlayer->AddTextToUI(gobletPlacedMessage);
		CurrentPlayer->SetClue(gobletPlacedClue);
	}
}

