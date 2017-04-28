// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "SphereInsertion.generated.h"

class ASecretDoor;
/**
 * 
 */
UCLASS()
class PROPHECY_API ASphereInsertion : public AInteractable
{
	GENERATED_BODY()

public:

	ASphereInsertion();
	void BeginPlay();
	virtual void InteractWithObject() override;
		
private:

	/**The index of the collectable needed to open this door*/
	UPROPERTY(EditAnywhere, Category = "Sphere Insertion")
	uint8 CollectableIndex;

	UPROPERTY(EditANywhere, Category = "Sphere Insertion")
	UStaticMeshComponent* Sphere;

	UPROPERTY(VisibleAnywhere, Category = "Sphere Insertion")
	ASecretDoor* HallwayDoor;
	
};
