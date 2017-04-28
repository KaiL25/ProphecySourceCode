// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "HunterEnemy.generated.h"


class UHunterAnimInstance;
class AHunterAIController;
class AProphecyCharacter;
class AEnemyTargetPoint;
/**
 * 
 */
UCLASS()
class PROPHECY_API AHunterEnemy : public AEnemy
{
	GENERATED_BODY()

	// Sets default values for this character's properties
	AHunterEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//UPROPERTY(EditAnywhere, Category = "Enemy")
	//class UBehaviorTree* BehaviorTree;
	//
	//UPROPERTY(VisibleAnywhere, Category = "Enemy")
	//class UPawnSensingComponent* PawnSensingComp;	

	/**Sets the canattack booleans in the animInstance and AIController to status*/
	virtual void CanAttackPlayer(bool bStatus) override;

	/*The player gets also passed in as a reference so that the enemy has a reference to the player once hit and can attack, or chase.*/
	virtual void ReceiveDamage(AProphecyCharacter* NewPlayer, int Amount) override;

	//*The function used when the enemy receives damage from anything, but the player*/
	//virtual void ReceiveDamage(int Amount) override;

	//virtual void SetCanDealdamage(bool bStatus) override;

	//TArray<AActor*> GetTargetPoints();	
	//
	//*Hearing function - will be executed when we hear a Pawn*/



	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume) override;

private:

	UPROPERTY(EditAnywhere, Category = "HunterEnemy")
	UHunterAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, Category = "HunterEnemy")
	AHunterAIController* AIController;

	///**A reference to the player when he gets seen*/
	//UPROPERTY(VisibleAnywhere, Category = "Enemy")
	//AProphecyCharacter* player;
	//
	//UPROPERTY(EditAnywhere, Category = "Enemy")		
	//int32 health;
	//
	///**The pawn is inside the player's melee range and therefore can attack the player*/
	//UPROPERTY(VisibleAnywhere, Category = "Enemy")
	//bool bCanAttackPlayer;
	//
	//UPROPERTY(EditAnywhere, Category = "Enemy")
	//TArray<AActor*> targetPoints;
	//
	//UPROPERTY(EditAnywhere, Category = "Enemy")
	//bool bDead;
	
	///**Gets set to true once the player has been spotted*/
	//UPROPERTY(VisibleAnywhere, Category = "Enemy")
	//bool bSeenPlayer;
		
	//UPROPERTY(EditAnywhere, Category = "VillagerEnemy")
	//UBoxComponent* WeaponCollider;
	//
	///**The pawn is in a attack animation right now and therefore can attack the player*/
	//UPROPERTY(VisibleAnywhere, Category = "Enemy")
	//bool bCanDealDamage;	
	//
	//UFUNCTION(BlueprintCallable, Category = "Enemy")
		//virtual void ReduceHealth(int32 amount) override;
	//
	UFUNCTION()
		virtual void OnSeePlayer(APawn* Pawn) override;
	//
	//
	//UFUNCTION()
	//void OnPlayerHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);

	
	
	
};
