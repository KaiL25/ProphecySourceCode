// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "Outhouse.generated.h"


class AStatue;
class AProphecyCharacter;

/**
 * 
 */
UCLASS()
class PROPHECY_API AOuthouse : public AInteractable
{
	GENERATED_BODY()
	
public:
		virtual void InteractWithObject() override;

		/**Used to give the outhouse a reference to the player to start communication between them*/
		void SetAProphecyCharacter(AProphecyCharacter* newPlayer);

private:

	AOuthouse();
	void BeginPlay();

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	UWorld* currentWorld;

	UPROPERTY(EditAnywhere, Category = "Outhouse")
	UStaticMeshComponent* water;

	UPROPERTY(EditAnywhere, Category = "Outhouse")
	UBoxComponent* waterHoleArea;

	UPROPERTY(EditAnywhere, Category = "Outhouse")
	UStaticMeshComponent* ironRod;
	
	UPROPERTY(VisibleAnywhere, Category = "Outhouse")
	bool holdingRod;

	UPROPERTY(VisibleAnywhere, Category = "Outhouse")
	AProphecyCharacter* player;

	UPROPERTY(VisibleAnywhere, Category = "Outhouse")
	AStatue* imrod;

	UPROPERTY(VisibleAnywhere, Category = "Outhouse")
	bool bImrodPickedUp;

	UPROPERTY(EditAnywhere, Category = "Outhouse")
	uint8 collectableIndex;

	FText outhouseMessage = NSLOCTEXT("Normal", "outhouseMessage", "This is an outhouse.");
	FText useHandsMessage = NSLOCTEXT("Normal", "useHandsMessage", "I am not going to use my hands to find the statue in there.");
	
};
