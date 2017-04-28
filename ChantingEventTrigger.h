// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventTrigger.h"
#include "ChantingEventTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API AChantingEventTrigger : public AEventTrigger
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void StartEvent() override;
	
	UPROPERTY(VisibleAnywhere)
	class ASoundArea* chantingSoundArea;

};
