// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Door.h"
#include "ProphecyCharacter.h"
#include "Engine.h"


ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
	bOpen = false;
	DoorAxis = CreateDefaultSubobject<USceneComponent>(TEXT("DoorAxis"));
	Mesh->SetupAttachment(DoorAxis);
	OpenDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenDoorTimeline"));	
	doorSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorSound"));
	doorSound->bAutoActivate = false;
	doorSound->RelativeLocation = FVector(0, 0, 0);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = TargetRotation = GetActorRotation();
	if (OpenCurve)
	{
		FOnTimelineFloat OpenFunction;

		OpenFunction.BindUFunction(this, FName("OpenDoor"));

		OpenDoorTimeline->AddInterpFloat(OpenCurve, OpenFunction);
		OpenDoorTimeline->SetLooping(false);
		TargetRotation.Yaw += MaxRotation;	
	}
}

void ADoor::UnlockDoor()
{
	if (CurrentPlayer)
	{
		if (CurrentPlayer->IsCollected(CollectableIndex))
		{
			Locked = false;
		}
		else
		{
			CurrentPlayer->AddTextToUI(closedText);
		}
	}
}

void ADoor::OpenDoor(float Value)
{	
	FRotator NewRotation = FMath::Lerp(OriginalRotation, TargetRotation, Value);

	DoorAxis->SetRelativeRotation(NewRotation);
}

void ADoor::InteractWithObject()
{
	if (!Locked)
	{
		/**If the door is not currently opening, or closing*/
		if (!OpenDoorTimeline->IsPlaying())
		{
			if (!bOpen)
			{
				OpenDoorTimeline->PlayFromStart();	
				doorSound->Play();
				bOpen = true;
			}
			else if (bOpen)
			{
				OpenDoorTimeline->ReverseFromEnd();		
				doorSound->Play();
				bOpen = false;
			}
		}
	}
	else if (Locked)
	{
		UnlockDoor();
	}
}