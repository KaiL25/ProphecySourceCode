// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "PlayerSoundLocation.h"
#include "Engine.h"


// Sets default values
APlayerSoundLocation::APlayerSoundLocation()
{
	playerSoundLocation = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerSoundLocation"));
	playerSoundLocation->SetupAttachment(RootComponent);
	this->Tags.Add("PlayerSoundLocation");	
}

// Called when the game starts or when spawned
void APlayerSoundLocation::BeginPlay()
{
	Super::BeginPlay();
	
}



void APlayerSoundLocation::SetPlayerSoundLocation(FVector newLocation)
{
	this->SetActorLocation(newLocation);
}


