// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "FloorSpikes.h"
#include "ProphecyCharacter.h"
#include "VillagerEnemyPawn.h"
#include "Engine.h"


// Sets default values
AFloorSpikes::AFloorSpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	spikes = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spikes"));	
	raiseTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("raiseTimeline"));
	bRaised = false;
	boxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	boxTrigger->SetupAttachment(floor);
	boxTrigger->bGenerateOverlapEvents = true;
	boxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorSpikes::OnPlayerEnterBoxCollider);
	boxTrigger->OnComponentEndOverlap.AddDynamic(this, &AFloorSpikes::OnPlayerExitBoxCollider);
	killVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("KillVolume"));
	killVolume->bGenerateOverlapEvents = true;
	killVolume->OnComponentBeginOverlap.AddDynamic(this, &AFloorSpikes::KillPlayer);
	killVolume->SetupAttachment(spikes);
	icon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));


}

// Called when the game starts or when spawned
void AFloorSpikes::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = targetLocation = spikes->GetComponentLocation();
	if (raiseCurve)
	{
		FOnTimelineFloat raiseFunction;

		raiseFunction.BindUFunction(this, FName("Raise"));

		raiseTimeline->AddInterpFloat(raiseCurve, raiseFunction);
		raiseTimeline->SetLooping(false);
		targetLocation.Z += maxDisplacement;
	}	
}

// Called every frame
void AFloorSpikes::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFloorSpikes::RaiseSpikes()
{
	/**If spikes are not already raised*/
	//if (!bRaised)
	//{
		raiseTimeline->PlayFromStart();		
		bRaised = true;
	//}	
}

void AFloorSpikes::LowerSpikes()
{
	raiseTimeline->Reverse();
	bRaised = false;
}

void AFloorSpikes::Raise(float Value)
{
	FVector NewVector = FMath::Lerp(originalLocation, targetLocation, Value);

	spikes->SetWorldLocation(NewVector);
}

void AFloorSpikes::OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player") || OtherActor->ActorHasTag("Enemy"))
	{
		RaiseSpikes();
	}
}

void AFloorSpikes::OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player") || OtherActor->ActorHasTag("Enemy"))
	{
		LowerSpikes();
	}
}

void AFloorSpikes::KillPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		AProphecyCharacter* player = Cast<AProphecyCharacter>(OtherActor);		
		player->ReceiveDamage(100);
	}
	else if (OtherActor->ActorHasTag("Enemy"))
	{
		AEnemy* tempEnemy = Cast<AEnemy>(OtherActor);
		tempEnemy->ReceiveDamage(1000);
	}
}

