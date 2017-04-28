// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "ProphecyCharacter.h"
#include "EventTrigger.h"
#include "Engine.h"


// Sets default values
AEventTrigger::AEventTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->bGenerateOverlapEvents = true;
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEventTrigger::OnPlayerEnterBoxCollider);	
	bActive = true;
}

// Called when the game starts or when spawned
void AEventTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEventTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEventTrigger::OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	
	if (OtherActor->ActorHasTag("Player"))
	{
		/*If the trigger is a TextTrigger call start event and pass in a player reference*/
		if (this->GetName().Contains("TextTrigger"))
		{
			AProphecyCharacter* player = Cast<AProphecyCharacter>(OtherActor);
			StartEvent(player);
		}
		/*If the trigger is a anything else call start event without arguments*/
		else
		{
			StartEvent();
		}	
	}
}

void AEventTrigger::StartEvent()
{

}

void AEventTrigger::StartEvent(AProphecyCharacter* Player)
{

}

void AEventTrigger::ActivateTrigger()
{
	
}

