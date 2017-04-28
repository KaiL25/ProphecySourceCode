// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTAttack.generated.h"

class AProphecyCharacter;
/**
 * 
 */
UCLASS()
class PROPHECY_API UBTAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	AProphecyCharacter* _player;
};
