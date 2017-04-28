// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "ChantingEventTrigger.h"
#include "SoundArea.h"

void AChantingEventTrigger::BeginPlay()
{
	for (TActorIterator<ASoundArea> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("ChantingSoundArea"))
		{
			chantingSoundArea = *ActorItr;
		}
	}
}

void AChantingEventTrigger::StartEvent()
{
	chantingSoundArea->SetSoundAreaActive(false);
}


