// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "ProphecyCharacter.h"
#include "ProphecyCharacterAnimInstance.h"
#include "Engine.h"


void UProphecyCharacterAnimInstance::UpdateAnimationProperties()
{
	//Get the pawn which is affected by our anim instance
	APawn* Pawn = TryGetPawnOwner();

	if (Pawn && !bPlayerDead)
	{
		//Update our falling property
		bIsFalling = Pawn->GetMovementComponent()->IsFalling();

		//Update our movement speed
		MovementSpeed = Pawn->GetVelocity().Size();

		//Update our direction
		Direction = this->CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());		
	}

	else if (bPlayerDead)
	{
		AProphecyCharacter* player = Cast<AProphecyCharacter>(Pawn);
		player->SetPlayerIsDead(true);
	}
}


void UProphecyCharacterAnimInstance::DrawSword()
{
	if (bIsSwordDrawn)
	{
		bIsSwordDrawn = false;
	}
	else
	{
		bIsSwordDrawn = true;
	}	
}

void UProphecyCharacterAnimInstance::Attack()
{
	if (!bSlash)
	{		
		bSlash = true;
	}
	else
	{
		bSlash = false;
	}
}

void UProphecyCharacterAnimInstance::EquipTorch()
{
	if (!bTorchEquipped)
	{
		bTorchEquipped = true;
	}
	else
	{
		bTorchEquipped = false;
	}
}

void UProphecyCharacterAnimInstance::SetBeingGrabbed(bool bStatus)
{
	bBeingGrabbed = bStatus;
}

void UProphecyCharacterAnimInstance::SetExaminingObject(bool bStatus)
{
	bExaminingObject = bStatus;
}

void UProphecyCharacterAnimInstance::SetPlayerDying(bool bStatus)
{
	bPlayerDying = bStatus;
}