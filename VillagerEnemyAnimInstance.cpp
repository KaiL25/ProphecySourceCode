// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "VillagerEnemyAnimInstance.h"
#include "VillagerEnemyPawn.h"
#include "Engine.h"

UVillagerEnemyAnimInstance::UVillagerEnemyAnimInstance()
{
	LeftHitReaction = CreateDefaultSubobject<UAnimMontage>(TEXT("LeftHitReaction"));
}

void  UVillagerEnemyAnimInstance::UpdateAnimationProperties()
{
	//Get the pawn which is affected by our anim instance
	APawn* Pawn = TryGetPawnOwner();
	body = Cast<AVillagerEnemyPawn>(TryGetPawnOwner());
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


void UVillagerEnemyAnimInstance::IsDead(bool status)
{	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "dead!");
	bDead = status;
}

void UVillagerEnemyAnimInstance::SetCanTakeDamage(bool bStatus)
{
	body->SetCanTakeDamage(bStatus);
}

void UVillagerEnemyAnimInstance::TakingDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Taking damage!");
	bTakingDamage = true;
}

void UVillagerEnemyAnimInstance::CanAttackPlayer(bool Status)
{
	bCanAttackPlayer = Status;
}

void UVillagerEnemyAnimInstance::SetPlayerSpotted()
{
	bSpottedPlayer = true;
}

bool UVillagerEnemyAnimInstance::GetWeaponDrawn()
{
	return bWeaponDrawn;
}

void UVillagerEnemyAnimInstance::SetHeardNoise()
{
	bHeardNoise = true;
}

void UVillagerEnemyAnimInstance::DrawingWeapon()
{
	body->AttachWeaponToWeaponSocket();
}

void UVillagerEnemyAnimInstance::CanDealDamage()
{
	if (body)
	{
		body->SetCanDealDamage(true);		
	}
}

void UVillagerEnemyAnimInstance::CannotDealDamage()
{
	if (body)
	{
		body->SetCanDealDamage(false);
	}
}


