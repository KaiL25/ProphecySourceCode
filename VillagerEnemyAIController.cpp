// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "VillagerEnemyAIController.h"
#include "VillagerEnemyPawn.h"
#include "EnemyTargetPoint.h"
#include "ProphecyCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine.h"

AVillagerEnemyAIController::AVillagerEnemyAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	LocationToGoKey = "LocationToGo";
}

void AVillagerEnemyAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	body = Cast<AVillagerEnemyPawn>(Pawn);

	if (body)
	{
		if (body->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(body->BehaviorTree->BlackboardAsset));
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTargetPoint::StaticClass(), EnemyTargetPoints);

	if (Pawn)
	{
		BehaviorComp->StartTree(*body->BehaviorTree);
	}
	
}

void AVillagerEnemyAIController::SetSeenTarget(APawn* Pawn)
{
	//Registers the Pawn that the AI has seen in the blackboard
	player = Cast<AProphecyCharacter>(Pawn);
	BlackboardComp->SetValueAsObject(target, Pawn);	
	BlackboardComp->SetValueAsBool("PlayerSpotted", true);
}

void AVillagerEnemyAIController::SetSensedTarget(APawn* NewTarget)
{
	player = Cast<AProphecyCharacter>(NewTarget);
	//Set a new target to follow
	if (BlackboardComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "SettingLocation");
		BlackboardComp->SetValueAsObject("NoiseLocation", player->torchFireSoundLocation);
		//BlackboardComp->SetValueAsBool("CanMove", true);
	}
}

void AVillagerEnemyAIController::CanAttackPlayer(bool Status)
{
	bCanAttackPlayer = Status;
	BlackboardComp->SetValueAsBool(attacking, Status);
}

void AVillagerEnemyAIController::BodyDead()
{
	BehaviorComp->StopTree();
}

bool AVillagerEnemyAIController::GetCanAttackPlayer()
{
	return bCanAttackPlayer;
}

AProphecyCharacter* AVillagerEnemyAIController::GetPlayerReference()
{
	return player;
}

void AVillagerEnemyAIController::SetCanMove()
{
	BlackboardComp->SetValueAsBool("canMove", true);
}

