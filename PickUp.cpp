// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "PickUp.h"
#include "ProphecyCharacter.h"
#include "Engine.h"


// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
	bCollectable = false;
	pickUpArea = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpArea"));
	pickUpArea->bGenerateOverlapEvents = true;
	pickUpArea->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnPlayerEnterPickUpArea);	
	pickUpArea->OnComponentEndOverlap.AddDynamic(this, &APickUp::OnPlayerExitPickUpArea);

	axis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Axis"));
	axis->SetupAttachment(pickUpArea);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));	
	mesh->SetupAttachment(axis);
	
	
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = axis->GetComponentLocation();
	originalRotation = axis->GetComponentRotation();
}

// Called every frame
void APickUp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void APickUp::OnPlayerEnterPickUpArea(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		SetPlayerCanPickUpObject(Cast<AProphecyCharacter>(OtherActor), true);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Inside of collider!");
	}
}


void APickUp::OnPlayerExitPickUpArea(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		AProphecyCharacter* player = Cast<AProphecyCharacter>(OtherActor);
		if (!player->GetIsExaminingObject())
		{
			SetPlayerCanPickUpObject(Cast<AProphecyCharacter>(OtherActor), false);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Deleteing reference");
		}
	}	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Outside of collider!");
}

void APickUp::SetPlayerCanPickUpObject(AProphecyCharacter* NewPlayerCharacter, bool NewStatus)
{
	if (NewPlayerCharacter)
	{
		NewPlayerCharacter->SetCanPickUp(NewStatus, this);
	}
}

FVector APickUp::GetOriginalLocation()
{
	if (this)
		return originalLocation;

	else
		return FVector(NULL,NULL,NULL);
}

FRotator APickUp::GetOriginalRotation()
{
	if (this)
		return originalRotation;

	else
		return  FRotator(NULL, NULL, NULL);
}

bool APickUp::IsCollectable()
{
	return bCollectable;
}

APickUp* APickUp::GetCollectable()
{
	return this;
}

uint8 APickUp::GetCollectableIndex()
{
	return collectableIndex;
}