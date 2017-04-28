// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "HunterAnimInstance.h"
#include "HunterEnemy.h"
#include "Engine.h"

UHunterAnimInstance::UHunterAnimInstance()
{
	LeftHitReaction = CreateDefaultSubobject<UAnimMontage>(TEXT("LeftHitReaction"));
}

void  UHunterAnimInstance::UpdateAnimationProperties()
{
	//Get the pawn which is affected by our anim instance
	APawn* Pawn = TryGetPawnOwner();
	body = Cast<AHunterEnemy>(TryGetPawnOwner());
	if (Pawn)
	{
		if (!bDead)
		{
			//Update our falling property
			bIsFalling = Pawn->GetMovementComponent()->IsFalling();

			//Update our movement speed
			MovementSpeed = Pawn->GetVelocity().Size();

			//Update our direction
			Direction = this->CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
		}
	}
}


void UHunterAnimInstance::IsDead(bool status)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "dead!");
	bDead = status;
}

void UHunterAnimInstance::SetCanTakeDamage(bool bStatus)
{
	body->SetCanTakeDamage(bStatus);
}

void UHunterAnimInstance::TakingDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Taking damage!");
	bTakingDamage = true;
}

void UHunterAnimInstance::CanAttackPlayer(bool Status)
{
	bCanAttackPlayer = Status;
}

void UHunterAnimInstance::SetPlayerSpotted()
{
	bSpottedPlayer = true;
}

void UHunterAnimInstance::SetHeardNoise()
{
	bHeardNoise = true;
}

void UHunterAnimInstance::CanDealDamage()
{
	if (body)
	{
		body->SetCanDealDamage(true);
	}
}

void UHunterAnimInstance::CannotDealDamage()
{
	if (body)
	{
		body->SetCanDealDamage(false);
	}
}






