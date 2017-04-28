// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "ProphecyGameMode.h"
#include "OutroSceneTrigger.h"


void AOutroSceneTrigger::StartEvent()
{
	AProphecyGameMode* gameMode = (AProphecyGameMode*)GetWorld()->GetAuthGameMode();
	gameMode->PlayOutroCutsceneMessage();
}

