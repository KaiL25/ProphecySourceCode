// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "Door.generated.h"


/**
 * 
 */
UCLASS()
class PROPHECY_API ADoor : public AInteractable
{
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
	ADoor();
	void BeginPlay();

public:			
		virtual void InteractWithObject() override;

private:

	UPROPERTY(EditAnywhere, Category = "Door")
	bool Locked;

	/**The index of the collectable needed to open this door*/
	UPROPERTY(EditAnywhere, Category = "Door")
	uint8 CollectableIndex;

	UPROPERTY(EditAnywhere, Category = "Door")
	UAudioComponent* doorSound;

	/**The point around which the door rotates*/
	UPROPERTY(EditAnywhere, Category = "Interactable")
	USceneComponent* DoorAxis;

	UPROPERTY(EditAnywhere, Category = "Interactable")
	int8 MaxRotation;

	/**Curve reference*/
	UPROPERTY(EditAnywhere, Category = "Interactable")
	UCurveFloat* OpenCurve;	

	FText closedText = NSLOCTEXT("Normal", "closedText", "The door is locked");

	/**Whether the door is open or not*/
	bool bOpen;
		
	FRotator OriginalRotation;
		
	FRotator TargetRotation;

	/**Timeline to make the door open*/
	class UTimelineComponent* OpenDoorTimeline;	
	
	void UnlockDoor();

	UFUNCTION()
	void OpenDoor(float Value);	
};
