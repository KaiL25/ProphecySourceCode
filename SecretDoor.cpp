// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "SecretDoor.h"
#include "Engine.h"


// Sets default values
ASecretDoor::ASecretDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecretDoor"));
	OpenDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenDoorTimeline"));
	LeftSmoke = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftSmoke"));
	RightSmoke = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightSmoke"));
	bOpen = false;
	slidingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("SlidingSound"));
	slidingSound->bAutoActivate = false;
	slidingSound->RelativeLocation = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void ASecretDoor::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = TargetLocation = GetActorLocation();
	if (OpenCurve)
	{
		FOnTimelineFloat OpenFunction;

		OpenFunction.BindUFunction(this, FName("Open"));

		OpenDoorTimeline->AddInterpFloat(OpenCurve, OpenFunction);
		OpenDoorTimeline->SetLooping(false);
		TargetLocation.Z += MaxDisplacement;
	}	
}

// Called every frame
void ASecretDoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASecretDoor::Open(float Value)
{
	FVector NewVector = FMath::Lerp(OriginalLocation, TargetLocation, Value);

	this->SetActorLocation(NewVector);
}

void ASecretDoor::OpenSecretDoor()
{
	/**If the door is not currently opening, or closing*/
	if (!bOpen)
	{
		
		OpenDoorTimeline->PlayFromStart();
		slidingSound->Play(6.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Secret door opening!");
		bOpen = true;
	}	
}

void ASecretDoor::CloseSecretDoor()
{
	if (bOpen)
	{
		OpenDoorTimeline->ReverseFromEnd();
		slidingSound->Play(6.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Secret door closing!");
		bOpen = false;
	}
}
