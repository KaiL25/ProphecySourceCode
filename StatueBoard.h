// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "StatueBoard.generated.h"


class ASecretDoor;
class ACleansingRitualWater;
/**
 * 
 */
UCLASS()
class PROPHECY_API AStatueBoard : public AInteractable
{
	GENERATED_BODY()

public: 

	virtual void InteractWithObject() override;

	

private:
	
	AStatueBoard();
	
	void BeginPlay();

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	UWorld* currentWorld;

	/**The index of the collectable needed to interact with this board*/
	UPROPERTY(EditAnywhere, Category = "StatueBoard")
	uint8 collectableIndex;
	
	UPROPERTY(EditAnywhere, Category = "StatueBoard")
	USkeletalMeshComponent* imrod;

	UPROPERTY(VisibleAnywhere, Category = "StatueBoard")
	ASecretDoor* secretDoor;

	UPROPERTY(VisibleAnywhere, Category = "StatueBoard")
	ACleansingRitualWater* poolWater;
	
};
