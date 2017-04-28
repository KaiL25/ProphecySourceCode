// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "HunterAIController.generated.h"

class AHunterEnemy;
class AProphecyCharacter;
/**
 * 
 */
UCLASS()
class PROPHECY_API AHunterAIController : public AAIController
{
	GENERATED_BODY()
private:

	/**This script was taken from http://orfeasel.com/creating-a-basic-patrol-ai/ */

	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;

	bool bCanAttackPlayer;

	TArray<AActor*> EnemyTargetPoints;
	AProphecyCharacter* player;


	virtual void Possess(APawn* Pawn) override;



public:

	AHunterAIController();

	/*Sets the new sensed target value inside our Blackboard values*/
	void SetSensedTarget(APawn* NewTarget);

	/**Blackboard key*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName target = "Target";

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName attacking = "Attacking";

	AHunterEnemy* body;

	void SetCanMove();

	/**Sets the sensed target in the blackboard*/
	void SetSeenTarget(APawn* Pawn);



	/**Gets called by BTAttack to know if it should start rotating the npc towards the player*/
	bool GetCanAttackPlayer();

	/**Gets called by BTAttack to get a reference to the player in order to rotate towards him*/
	AProphecyCharacter* GetPlayerReference();

	/**Sets bCanAttackPlayerToTrue, so that the attack animation gets played.*/
	void CanAttackPlayer(bool Status);

	/**Used to stop the Behavior Tree from running when the enemy is dead*/
	void BodyDead();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return EnemyTargetPoints; }	
};
