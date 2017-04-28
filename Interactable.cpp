// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Interactable.h"
#include "ProphecyCharacter.h"
#include "Engine.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Mesh);
	BoxCollision->bGenerateOverlapEvents = true;
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnPlayerEnterBoxCollider);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnPlayerExitBoxCollider);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractable::OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		SetPlayerCanInteractWithObject(Cast<AProphecyCharacter>(OtherActor), true);		
		CurrentPlayer = Cast<AProphecyCharacter>(OtherActor);
	}
}


void AInteractable::OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		SetPlayerCanInteractWithObject(Cast<AProphecyCharacter>(OtherActor), false);
		CurrentPlayer = NULL;
	}
}

void AInteractable::SetPlayerCanInteractWithObject(AProphecyCharacter* NewPlayerCharacter, bool NewStatus)
{
	NewPlayerCharacter->SetCanInteract(NewStatus, this);
}

void AInteractable::InteractWithObject()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Interacting!");
}

