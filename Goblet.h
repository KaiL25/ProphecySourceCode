// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "Goblet.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API AGoblet : public APickUp
{
	GENERATED_BODY()

public:	

	void SetFilledWithWater();

private:

	UPROPERTY(VisibleAnywhere, Category = "Goblet")
	bool FilledWithWater;
	
	
	
};
