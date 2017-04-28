// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "CleansingRitualWater.h"
#include "ProphecyCharacter.h"
#include "Engine.h"


// Sets default values
ACleansingRitualWater::ACleansingRitualWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));
    raiseTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("raiseTimeline"));
	bRaised = false;
	this->Tags.Add("CleansingRitualPool");
	waterTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("WaterTrigger"));
	waterTrigger->SetupAttachment(water);
	waterTrigger->bGenerateOverlapEvents = true;
	waterTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACleansingRitualWater::OnPlayerEnterBoxCollider);
	waterTrigger->OnComponentEndOverlap.AddDynamic(this, &ACleansingRitualWater::OnPlayerExitBoxCollider);
}

// Called when the game starts or when spawned
void ACleansingRitualWater::BeginPlay()
{
	Super::BeginPlay();
	
	originalLocation = targetLocation = GetActorLocation();
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
void ACleansingRitualWater::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACleansingRitualWater::Raise(float Value)
{
	FVector NewVector = FMath::Lerp(originalLocation, targetLocation, Value);

	this->SetActorLocation(NewVector);
}

void ACleansingRitualWater::RaiseWaterLevel()
{
	/**If water is not already raised*/
	if (!bRaised)
	{
		raiseTimeline->PlayFromStart();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Raising water level!");
		bRaised = true;
	}
}

void ACleansingRitualWater::OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		AProphecyCharacter* player = Cast<AProphecyCharacter>(OtherActor);
		player->EnteredWater(true);
	}
}

void ACleansingRitualWater::OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		AProphecyCharacter* player = Cast<AProphecyCharacter>(OtherActor);
		player->EnteredWater(false);
	}
}