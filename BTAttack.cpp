// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "BTAttack.h"
#include "ProphecyCharacter.h"
#include "VillagerEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine.h"

EBTNodeResult::Type UBTAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AVillagerEnemyAIController* AICon = Cast<AVillagerEnemyAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if(AICon)
	{		
		BlackboardComp->ClearValue("NoiseLocation");
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}



