// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "StatueBoard.h"
#include "SecretDoor.h"
#include "ProphecyCharacter.h"
#include "CleansingRitualWater.h"
#include "Engine.h"

AStatueBoard::AStatueBoard()
{
	imrod = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Imrod"));
	imrod->SetupAttachment(Mesh);
	
	
}

void AStatueBoard::BeginPlay()
{
	Super::BeginPlay();
	currentWorld = GetWorld();
	if (currentWorld)
	{
		imrod->SetVisibility(false);
			;
		for (TActorIterator<ASecretDoor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr->ActorHasTag("CleansingRitualSecretDoor"))
			{
				secretDoor = *ActorItr;
			}
		}

		for (TActorIterator<ACleansingRitualWater> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr->ActorHasTag("CleansingRitualPool"))
			{
				poolWater = *ActorItr;
			}
		}

	}
}

void AStatueBoard::InteractWithObject()
{
	if (!imrod->bVisible && CurrentPlayer->IsCollected(collectableIndex))
	{
		imrod->SetVisibility(true);
		secretDoor->OpenSecretDoor();
		poolWater->RaiseWaterLevel();
	}

}