// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "CloseAltarRoomSecretDoorTrigger.h"
#include "SecretDoor.h"
#include "Engine.h"

void ACloseAltarRoomSecretDoorTrigger::BeginPlay()
{
	for (TActorIterator<ASecretDoor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("AltarRoomSecretDoor"))
		{
			AltarRoomDoor = *ActorItr;
		}
	}
}

void ACloseAltarRoomSecretDoorTrigger::StartEvent()
{
	if (!triggered)
	{
		triggered = true;
		AltarRoomDoor->CloseSecretDoor();
	}
	
}


