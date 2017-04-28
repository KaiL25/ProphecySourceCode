// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Signboard.h"
#include "ProphecyCharacter.h"
#include "Engine.h"


// Sets default values
ASignboard::ASignboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
	Board = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->bGenerateOverlapEvents = true;
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASignboard::OnPlayerEnterBoxCollider);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ASignboard::OnPlayerExitBoxCollider);
	
}

// Called when the game starts or when spawned
void ASignboard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASignboard::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASignboard::OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		SetPlayerCanInteractWithPaintingSigns(Cast<AProphecyCharacter>(OtherActor), true);
		AProphecyCharacter* player = Cast<AProphecyCharacter>(OtherActor);
		if (!bHasBeenPrintedToScreen)
		{
			player->AddTextToUI(runesMessage);
			bHasBeenPrintedToScreen = true;
		}
	}
}

void ASignboard::OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		SetPlayerCanInteractWithPaintingSigns(Cast<AProphecyCharacter>(OtherActor), false);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Outside of collider!");
	}
}

void ASignboard::SetPlayerCanInteractWithPaintingSigns(AProphecyCharacter* NewPlayerCharacter, bool NewStatus)
{
	NewPlayerCharacter->SetCanInteractWithPaintingPuzzleSigns(NewStatus);
}

