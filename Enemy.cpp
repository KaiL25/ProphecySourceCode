// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Enemy.h"
#include "ProphecyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyTargetPoint.h"
#include "Engine.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	health = 50;
	bCanTakeDamage = true;
	this->Tags.Add("Enemy");
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(60.f);
	PawnSensingComp->SightRadius = 1000;	
	damageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollider"));
	//damageCollider->SetupAttachment(Weapon);
	damageCollider->bGenerateOverlapEvents = true;
	damageCollider->OnComponentBeginOverlap.AddDynamic(this, &AVillagerEnemyPawn::OnPlayerHit);	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemy::OnSeePlayer);
		//Registering the delegate which will fire when we hear something
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AEnemy::OnHearNoise);
	}
	
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (bCanAttackPlayer)
	{
		if (player && !bDead)
		{
			/*The Max is 251991*/
			FRotator rotToPlayer;
			rotToPlayer = FRotationMatrix::MakeFromX(player->GetActorLocation() - this->GetActorLocation()).Rotator();
			SetActorRotation(rotToPlayer);
		}
	}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AEnemy::PlayerDied()
{
	bCanAttackPlayer = false;	
}

void AEnemy::SetCanTakeDamage(bool bStatus)
{
	bCanTakeDamage = bStatus;
}

void AEnemy::ReceiveDamage(AProphecyCharacter* NewPlayer, int Amount)
{
	//if (!player)
	//{
	//	player = NewPlayer;
	//	//AIController->SetSeenTarget(player);
	//	//AnimInstance->SetPlayerSpotted();
	//}
	//ReduceHealth(Amount);
}

void AEnemy::ReceiveDamage(int Amount)
{
	ReduceHealth(Amount);
}

void AEnemy::ReduceHealth(int amount)
{
	if (health <= 0)
	{
		bDead = true;
		//DEATH ANIMATION ETC.
		//AnimInstance->IsDead(bDead);
		//AIController->BodyDead();
	}
	else if (health > 0)
	{
		health -= amount;
		//AnimInstance->TakingDamage();
	}
}

void AEnemy::SetCanDealDamage(bool bStatus)
{
	bCanDealDamage = bStatus;
}

TArray<AActor*> AEnemy::GetTargetPoints()
{
	return targetPoints;
}

void AEnemy::OnSeePlayer(APawn* Pawn)
{
	//if (!Pawn)
	//{
	//	//this->PawnSensingComp->CanSenseAnything();
	//	//this->PawnSensingComp->sense
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Doesn't see player.");
	//}
	//bSeenPlayer = true;
	//player = Cast<AProphecyCharacter>(Pawn);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Sees player.");
	////Set the seen target on the blackboard	
	////if (AIController)
	////{
	//	//AIController->SetSeenTarget(Pawn);
	//	//AnimInstance->SetPlayerSpotted();
	////}
}

void AEnemy::CanAttackPlayer(bool Status)
{
	//if (bSeenPlayer)
	//{
	//	bCanAttackPlayer = Status;
	//	//AnimInstance->CanAttackPlayer(Status);
	//	//AIController->CanAttackPlayer(Status);
	//}
}

void AEnemy::OnPlayerHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{		
		if (bCanDealDamage)
		{			
			if (player != NULL)
			{				
				player->ReceiveDamage(10);
				bCanDealDamage = false;
				if (this->GetName().Contains("TheHunter") && player->InMeleeRangeOfPlayer() == this)
				{
					player->IsBeingGrabbed(true);
				}
			}

		}
	}
}

void AEnemy::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Heard a noise");
	//We don't want to hear ourselves
	//if (AIController &&PawnInstigator != this)
	//{
	//	//Updates our target based on what we've heard
	//	AIController->SetSensedTarget(PawnInstigator);
	//	AnimInstance->SetHeardNoise();
	//}
}

