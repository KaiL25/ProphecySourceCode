// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "ProphecyCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API UProphecyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	/**Toggles bIsSwordDrawn to cause the ABP to draw or sheathe the sword*/
	void DrawSword();
	void Attack();
	void EquipTorch();
	/**Gets called by ProphecyCharacter when TheHunter grabs him.
	   Is used to enable the being held animation and then lead to the death animation.*/
	void SetBeingGrabbed(bool bStatus);
	void SetExaminingObject(bool bStatus);
	void SetPlayerDying(bool bStatus);

protected:	
	/*True means that we're currently in air - or falling*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsSwordDrawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSlash;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bTorchEquipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bBeingGrabbed;

	//The player is at 0 hp, but the death animation still has to be played
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bPlayerDying;

	//The player has reached the end of the death animation
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bPlayerDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bExaminingObject;

	/*Holds the current speed of our character*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Direction;

	/*Updates the above properties*/
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();
	
	
	
};
