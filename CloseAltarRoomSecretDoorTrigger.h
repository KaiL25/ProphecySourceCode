// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventTrigger.h"
#include "CloseAltarRoomSecretDoorTrigger.generated.h"

class ASecretDoor;
/**
 * 
 */
UCLASS()
class PROPHECY_API ACloseAltarRoomSecretDoorTrigger : public AEventTrigger
{
	GENERATED_BODY()

		//ACloseAltarRoomSecretDoorTrigger();
		void BeginPlay();

private:

		virtual void StartEvent() override;

		UPROPERTY(VisibleAnywhere, Category = "CloseAltarRoomSecretDoorTrigger")
		ASecretDoor* AltarRoomDoor;
	
};
