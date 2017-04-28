// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "HunterAIController.h"
#include "HunterEnemy.h"
#include "EnemyTargetPoint.h"
#include "ProphecyCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine.h"

AHunterAIController::AHunterAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	LocationToGoKey = "LocationToGo";
}

void AHunterAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	body = Cast<AHunterEnemy>(Pawn);

	if (body)
	{
		if (body->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(body->BehaviorTree->BlackboardAsset));
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTargetPoint::StaticClass(), EnemyTargetPoints);

	BehaviorComp->StartTree(*body->BehaviorTree);

}

void AHunterAIController::SetSeenTarget(APawn* Pawn)
{
	//Registers the Pawn that the AI has seen in the blackboard
	player = Cast<AProphecyCharacter>(Pawn);
	BlackboardComp->SetValueAsObject(target, Pawn);
	BlackboardComp->SetValueAsBool("PlayerSpotted", true);
}

void AHunterAIController::SetSensedTarget(APawn* NewTarget)
{
	player = Cast<AProphecyCharacter>(NewTarget);
	//Set a new target to follow
	if (BlackboardComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "SettingLocation");
//		BlackboardComp->SetValueAsObject("NoiseLocation", player->torchFireSoundLocation);		
	}
}

void AHunterAIController::CanAttackPlayer(bool Status)
{
	bCanAttackPlayer = Status;
	BlackboardComp->SetValueAsBool(attacking, Status);
}

void AHunterAIController::BodyDead()
{
	BehaviorComp->StopTree();
}

bool AHunterAIController::GetCanAttackPlayer()
{
	return bCanAttackPlayer;
}

AProphecyCharacter* AHunterAIController::GetPlayerReference()
{
	return player;
}

void AHunterAIController::SetCanMove()
{
	BlackboardComp->SetValueAsBool("canMove", true);
}





