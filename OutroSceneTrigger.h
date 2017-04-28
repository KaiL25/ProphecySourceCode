// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventTrigger.h"
#include "OutroSceneTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API AOutroSceneTrigger : public AEventTrigger
{
	GENERATED_BODY()

private:    

	virtual void StartEvent() override;
	
};
