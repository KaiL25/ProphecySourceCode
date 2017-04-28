// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "VillagerEnemyPawn.h"
#include "VillagerEnemyAnimInstance.h"
#include "VillagerEnemyAIController.h"
#include "ProphecyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyTargetPoint.h"
#include "Engine.h"


// Sets default values
AVillagerEnemyPawn::AVillagerEnemyPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	//health = 50;
	//this->Tags.Add("Enemy");
	//PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	////Set the peripheral vision angle to 90 degrees
	//PawnSensingComp->SetPeripheralVisionAngle(60.f);
	//PawnSensingComp->SightRadius = 1000;
	
	weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	weapon->SetupAttachment(this->GetMesh(), "WeaponSheathe");	
	//WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollider"));
	damageCollider->SetupAttachment(weapon);
	//WeaponCollider->bGenerateOverlapEvents = true;
	//WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AVillagerEnemyPawn::OnPlayerHit);	
}

// Called when the game starts or when spawned
void AVillagerEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UVillagerEnemyAnimInstance>(this->GetMesh()->GetAnimInstance());
	AIController = Cast<AVillagerEnemyAIController>(GetController());

	//if (PawnSensingComp)
	//{
	//	PawnSensingComp->OnSeePawn.AddDynamic(this, &AVillagerEnemyPawn::OnSeePlayer);	
	//	//Registering the delegate which will fire when we hear something
	//	PawnSensingComp->OnHearNoise.AddDynamic(this, &AVillagerEnemyPawn::OnHearNoise);
	//}
	//if (this->GetName().Contains("TheHunter"))
	//{
	//	AIController->SetCanMove();
	//}
}

// Called every frame
void AVillagerEnemyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//Rotation towards the player
	//if (bCanAttackPlayer)
	//{		
	//	if (player && !bDead)
	//	{	
	//		/*The Max is 251991*/
	//		FRotator rotToPlayer;
	//		rotToPlayer = FRotationMatrix::MakeFromX(player->GetActorLocation() - this->GetActorLocation()).Rotator();			
	//		SetActorRotation(rotToPlayer);
	//	}
	//}

	//if (AnimInstance->GetWeaponDrawn() && !this->GetName().Contains("TheHunter"))
	//{		
	//	Weapon->AttachSocketName = "Weapon";		
	//}

	//if (player != NULL)
	//{
	//	if (player->IsPlayerDead())
	//	{
	//		bCanAttackPlayer = false;
	//		AnimInstance->CanAttackPlayer(false);
	//		AIController->CanAttackPlayer(false);
	//	}
	//}

	//if (PawnSensingComp->OnSeePawn())
	//{
	//	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Sees player.");
	//}
	//
	//else
	//{
	//	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Doesn't see player.");
	//}
	//if (AnimInstance->GetCurrentActiveMontage()->GetName() == "Attack")
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Can damage!");
	//	bCanDealDamage = true;
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Cannot damage!");
	//	bCanDealDamage = false;
	//}

}

// Called to bind functionality to input
void AVillagerEnemyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AVillagerEnemyPawn::AttachWeaponToWeaponSocket()
{	
	weapon->AttachSocketName = "Weapon";
}

void AVillagerEnemyPawn::ReceiveDamage(AProphecyCharacter* NewPlayer, int Amount)
{
	if (!player)
	{
		player = NewPlayer;
		AIController->SetSeenTarget(player);
		AnimInstance->SetPlayerSpotted();
	}
	ReduceHealth(Amount);
}

void AVillagerEnemyPawn::ReduceHealth(int amount)
{		
	if (health <= 0)
	{
		PawnSensingComp->Deactivate();
		bDead = true;
		//DEATH ANIMATION ETC.
		AnimInstance->IsDead(bDead);
		AIController->BodyDead();
	}

	if (bCanTakeDamage)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "HitEnemy ");
		if (health > 0)
		{
			health -= amount;
			AnimInstance->TakingDamage();
		}
	}
}

//void AVillagerEnemyPawn::SetCanDealdamage(bool bStatus)
//{
//	bCanDealDamage = bStatus;
//}
//
//TArray<AActor*> AVillagerEnemyPawn::GetTargetPoints()
//{
//	return targetPoints;
//}
//
void AVillagerEnemyPawn::OnSeePlayer(APawn* Pawn)
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

void AVillagerEnemyPawn::CanAttackPlayer(bool Status)
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

void AVillagerEnemyPawn::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{		
	if (!bDead)
	{
		//We don't want to hear ourselves
		if (AIController &&PawnInstigator != this)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Heard a noise");
			//Updates our target based on what we've heard
			AIController->SetSensedTarget(PawnInstigator);
			AnimInstance->SetHeardNoise();
		}
	}
}