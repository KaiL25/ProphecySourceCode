// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AProphecyCharacter;
class AEnemyTargetPoint;

UCLASS()
class PROPHECY_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	class UPawnSensingComponent* PawnSensingComp;

	/**Sets the canAttack booleans in the animInstance and AIController to status*/
	virtual void CanAttackPlayer(bool bStatus);

	UFUNCTION()
	void SetCanTakeDamage(bool bStatus);

	/*The player gets also passed in as a reference so that the enemy has a reference to the player once hit and can attack, or chase.*/
	virtual void ReceiveDamage(AProphecyCharacter* NewPlayer, int Amount);

	/*The function used when the enemy receives damage from anything, but the player*/
	void ReceiveDamage(int Amount);

	void SetCanDealDamage(bool bStatus);

	TArray<AActor*> GetTargetPoints();

	//Stops the enemy from chasing and attacking the player.
	void PlayerDied();

	/*Hearing function - will be executed when we hear a Pawn*/
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);



protected:

	/**A reference to the player when he gets seen*/
	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	AProphecyCharacter* player;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 health;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UBoxComponent* damageCollider;

	/**The pawn is inside the player's melee range and therefore can attack the player*/
	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	bool bCanAttackPlayer;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	bool bCanTakeDamage;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	bool bDead;

	/**Gets set to true once the player has been spotted*/
	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	bool bSeenPlayer;
	
private:	

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TArray<AActor*> targetPoints;	
	
	/**The pawn is in a attack animation right now and therefore can attack the player*/
	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	bool bCanDealDamage;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void ReduceHealth(int32 amount);

	UFUNCTION()
	virtual void OnSeePlayer(APawn* Pawn);


	UFUNCTION()
	void OnPlayerHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
	
};
