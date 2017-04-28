// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "Water.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API AWater : public AInteractable
{
	GENERATED_BODY()
	
public:

	AWater();
	void BeginPlay();
	virtual void InteractWithObject() override;

private:

		/**The index of the collectable needed to open this door*/
		UPROPERTY(EditAnywhere, Category = "Water")
		uint8 collectableIndex;
		/*Der Partikeleffekt fuer das Wasser*/
		UPROPERTY(EditAnywhere, Category = "Water")
		UParticleSystemComponent* splash;
	
};
