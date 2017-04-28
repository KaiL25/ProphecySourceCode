// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "GobletPedestal.generated.h"


class ASecretDoor;
/**
 * 
 */
UCLASS()
class PROPHECY_API AGobletPedestal : public AInteractable
{
	GENERATED_BODY()

public: 

	virtual void InteractWithObject() override;

private:

	AGobletPedestal();

	void BeginPlay();

	/**The index of the collectable needed to open this door*/
	UPROPERTY(EditAnywhere, Category = "GobletPedestal")
	uint8 CollectableIndex;

	UPROPERTY(VisibleAnywhere, Category = "GobletPedestal")
	UStaticMeshComponent* Goblet;

	UPROPERTY(VisibleAnywhere, Category = "GobletPedestal")
	UStaticMeshComponent* Water;

	UPROPERTY(VisibleAnywhere, Category = "GobletPedestal")
	ASecretDoor* AltarRoomDoor;

	FText gobletPlacementMessage = NSLOCTEXT("Normal", "gobletPlacementMessage", "This looks like something is supposed to be placed on here...");
	FText gobletPlacementClue = NSLOCTEXT("Normal", "gobletPlacementClue", "I need to find the object that is \nsupposed to be placed on the pedestal.");
	FText gobletContentMessage = NSLOCTEXT("Normal", "gobletContentMessage", "It seems like the goblet is not heavy enough. Perhaps if I fill it with something...");
	FText gobletContentClue = NSLOCTEXT("Normal", "gobletContentClue", "The goblet needs to be heavier.");
	FText gobletPlacedMessage = NSLOCTEXT("Normal", "gobletPlacedMessage", "I can hear stone grinding. I must have opened a secret passage.");
	FText gobletPlacedClue = NSLOCTEXT("Normal", "gobletPlacedClue", "I need to push on.");
	
};
