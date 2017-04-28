// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Outhouse.h"
#include "ProphecyCharacter.h"
#include "Statue.h"
#include "Engine.h"


AOuthouse::AOuthouse()
{	
	water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));
	water->SetupAttachment(RootComponent);
	waterHoleArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WaterHoleArea"));
	waterHoleArea->SetupAttachment(water);
	ironRod = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IronRod"));
	ironRod->SetupAttachment(waterHoleArea);
	this->Tags.Add("Outhouse");
}

void AOuthouse::BeginPlay()
{
	Super::BeginPlay();
	currentWorld = GetWorld();
	if (currentWorld)
	{

		for (TActorIterator<AStatue> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr->ActorHasTag("Imrod"))
			{
				imrod = *ActorItr;
			}
		}
	}
}

void AOuthouse::InteractWithObject()
{
	/*if (holdingRod)
	{
		holdingRod = false;
		player->SetOuthouseRod(NULL);
	}

	else
	{
		holdingRod = true;
		player->SetOuthouseRod(ironRod);

	}*/
	//If the player has not already picked up the imrod statue...
	if (!bImrodPickedUp)
	{		
		//If the player has the iron rod needed to interact with the outhouse...
		if (player->IsCollected(collectableIndex))
		{
			player->SetCanPickUp(true, imrod);
			bImrodPickedUp = true;
		}
		else if(player->IsOuthouseLetterRead())
		{
			player->AddTextToUI(useHandsMessage);
		}

		else
		{
			player->AddTextToUI(outhouseMessage);
		}
	}
	
}

void  AOuthouse::SetAProphecyCharacter(AProphecyCharacter* newPlayer)
{
	player = newPlayer;
}