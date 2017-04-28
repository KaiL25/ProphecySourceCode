// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "Lever.generated.h"

class ADoor;

/**
 * 
 */
UCLASS()
class PROPHECY_API ALever : public AInteractable
{
	GENERATED_BODY()

public:
		
	ALever();
	void BeginPlay();
	virtual void InteractWithObject() override;

private:

	
	/**The Axis around which the lever rotates*/
	UPROPERTY(EditAnywhere, Category = "Lever")
	USceneComponent* RotationAxis;
	
	/**Reference to the gate which leads to the altar room
	   Used to open the gate upon activation of the lever*/
	UPROPERTY(VisibleAnywhere, Category = "Lever")
	ADoor* CaveGateLeftDoor;

	UPROPERTY(VisibleAnywhere, Category = "Lever")
	ADoor* CaveGateRightDoor;

	UPROPERTY(EditAnywhere, Category = "Lever")
	int8 MaxRotation;

	/**Curve reference*/
	UPROPERTY(EditAnywhere, Category = "Lever")
	UCurveFloat* RotateCurve;

	/**Whether the door is open or not*/
	bool bOpen;

	FRotator OriginalRotation;

	FRotator TargetRotation;

	/**Timeline to make the door open*/
	class UTimelineComponent* RotateLeverTimeline;

	UFUNCTION()
	void RotateLever(float Value);

	
	
};
