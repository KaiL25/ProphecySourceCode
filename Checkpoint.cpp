// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Checkpoint.h"
#include "ProphecyGameInstance.h"
#include "Engine.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->SetupAttachment(RootComponent);
	boxCollision->bGenerateOverlapEvents = true;
	boxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnEnterBoxCollision);	
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpoint::OnEnterBoxCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{		
		UProphecyGameInstance* prophecyGameInstance = Cast<UProphecyGameInstance>(GetWorld()->GetGameInstance());
		prophecyGameInstance->SetCheckpointActive(checkpointIndex);
	}
}

