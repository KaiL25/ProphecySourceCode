// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "HunterEnemy.h"
#include "HunterAnimInstance.h"
#include "HunterAIController.h"
#include "ProphecyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyTargetPoint.h"
#include "Engine.h"

// Sets default values
AHunterEnemy::AHunterEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	damageCollider->AttachSocketName = "Weapon";
}

// Called when the game starts or when spawned
void AHunterEnemy::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UHunterAnimInstance>(this->GetMesh()->GetAnimInstance());
	AIController = Cast<AHunterAIController>(GetController());	
}

// Called every frame
void AHunterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);		

	if (player != NULL)
	{
		if (player->IsPlayerDead())
		{
			bCanAttackPlayer = false;
			AnimInstance->CanAttackPlayer(false);
			AIController->CanAttackPlayer(false);
		}
	}
}

// Called to bind functionality to input
void AHunterEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AHunterEnemy::ReceiveDamage(AProphecyCharacter* NewPlayer, int Amount)
{
	if (!player)
	{
		player = NewPlayer;
		AIController->SetSeenTarget(player);
		AnimInstance->SetPlayerSpotted();
	}	
}

void AHunterEnemy::OnSeePlayer(APawn* Pawn)
{
	if (!Pawn)
	{
		//this->PawnSensingComp->CanSenseAnything();
		//this->PawnSensingComp->sense 
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Doesn't see player.");
	}
	bSeenPlayer = true;
	player = Cast<AProphecyCharacter>(Pawn);
	//Set the seen target on the blackboard	
	if (AIController)
	{
		AIController->SetSeenTarget(Pawn);
		AnimInstance->SetPlayerSpotted();
		if (!bSeenPlayer)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Sees player in child.");
		}
	}
}

void AHunterEnemy::CanAttackPlayer(bool Status)
{
	if (bSeenPlayer)
	{
		bCanAttackPlayer = Status;
		AnimInstance->CanAttackPlayer(Status);
		AIController->CanAttackPlayer(Status);
	}
}

//void AVillagerEnemyPawn::OnPlayerHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
//{
//	if (OtherActor->ActorHasTag("Player"))
//	{		
//		if (bCanDealDamage)
//		{			
//			if (player != NULL)
//			{
//				player->ReceiveDamage(10);
//				if (this->GetName().Contains("TheHunter") && player->InMeleeRangeOfPlayer() == this)
//				{					
//					player->IsBeingGrabbed(true);
//				}
//			}
//			
//		}
//	}
//}

void AHunterEnemy::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!bDead)
	{
		//We don't want to hear ourselves
		//if (AIController &&PawnInstigator != this)
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Heard a noise");
		//	//Updates our target based on what we've heard
		//	AIController->SetSensedTarget(PawnInstigator);
		//	AnimInstance->SetHeardNoise();
		//}
	}
}


