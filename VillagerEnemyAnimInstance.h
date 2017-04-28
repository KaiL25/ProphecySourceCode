// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "VillagerEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API UVillagerEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:


	UVillagerEnemyAnimInstance();

	void IsDead(bool status);

	void TakingDamage();

	/**Tells the villager pawn whether to attach the weapon to the hand socket or not*/
	bool GetWeaponDrawn();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetCanTakeDamage(bool bStatus);

	/**Sets bCanAttackPlayerToTrue, so that the attack animation gets played.*/
	void CanAttackPlayer(bool Status);

	/**Once the player is spotted the enemies do not return to praying, that is why it can only be set to true*/
	void SetPlayerSpotted();

	void SetHeardNoise();	

	UFUNCTION(BlueprintCallable, Category = "VillagerEnemy")
	void DrawingWeapon();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void CanDealDamage();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void CannotDealDamage();
	
protected:

	/*True means that we're currently in air - or falling*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFalling;
	
	/*Holds the current speed of our character*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWeaponDrawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bZombified;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bTakingDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanAttackPlayer;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHeardNoise;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bSpottedPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* LeftHitReaction;

	
	/*Updates the above properties*/
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();

private:

	class AVillagerEnemyPawn* body;
	
};
