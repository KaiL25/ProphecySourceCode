// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "BTTargetPointSelection.h"
#include "EnemyTargetPoint.h"
#include "VillagerEnemyPawn.h"
#include "VillagerEnemyAIController.h"
#include "HunterEnemy.h"
#include "HunterAIController.h"
#include "Engine.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//The villagers do not really need to know the patrol points since none of them patrols at the moment.
	//AVillagerEnemyAIController* AICon = Cast<AVillagerEnemyAIController>(OwnerComp.GetAIOwner());
	//AVillagerEnemyPawn* temp = Cast<AVillagerEnemyPawn>(AICon->GetPawn());
	
	AHunterAIController* AICon = Cast<AHunterAIController>(OwnerComp.GetAIOwner());
	AHunterEnemy* temp = Cast<AHunterEnemy>(AICon->GetPawn());
	
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		AEnemyTargetPoint* CurrentPoint = Cast<AEnemyTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		
		TArray<AActor*> AvailableTargetPoints = temp->GetTargetPoints();
		

		int32 RandomIndex;
		
		AEnemyTargetPoint* NextTargetPoint = nullptr;

		/**If there is more than just one target point in the scene choose one, go there and then choose the next one randomly.*/
		if (AvailableTargetPoints.Num() > 1)
		{
			do
			{
				RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);

				NextTargetPoint = Cast<AEnemyTargetPoint>(AvailableTargetPoints[RandomIndex]);
			} while (CurrentPoint == NextTargetPoint);

			BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

			return EBTNodeResult::Succeeded;
		}
		/**If there is only one target point in the array make it the next target point and go there.*/
		else if (AvailableTargetPoints.Num() == 1)
		{			
			NextTargetPoint = Cast<AEnemyTargetPoint>(AvailableTargetPoints[0]);
			BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
			return EBTNodeResult::Succeeded;
		}
	}	
	return EBTNodeResult::Failed;
}



