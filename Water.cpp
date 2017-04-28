// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Water.h"
#include "ProphecyCharacter.h"

AWater::AWater()
{
	splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Splash"));
}

void AWater::BeginPlay()
{

}

void AWater::InteractWithObject()
{	
	/*If the goblet is collected...*/
	if (CurrentPlayer->IsCollected(collectableIndex))
	{
		/*If the goblet is not already filled with water...*/
		if (!CurrentPlayer->GetFilledWithWater())
		{
			splash->ActivateSystem();
			CurrentPlayer->SetGobletFilledWithWater();
		}
	}	
}