// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerSoundLocation.generated.h"

UCLASS()
class PROPHECY_API APlayerSoundLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSoundLocation();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
	void SetPlayerSoundLocation(FVector newLocation);

private:


	USceneComponent* playerSoundLocation;
	
};
