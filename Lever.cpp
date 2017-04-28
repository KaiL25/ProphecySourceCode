// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Lever.h"
#include "Door.h"
#include "Engine.h"

ALever::ALever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bOpen = false;
	RotationAxis = CreateDefaultSubobject<USceneComponent>(TEXT("RotationAxis"));
	Mesh->SetupAttachment(RotationAxis);
	RotateLeverTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("RotateLeverTimeline"));
}

void ALever::BeginPlay()
{
	for (TActorIterator<ADoor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->ActorHasTag("CaveGateLeft"))
		{
			CaveGateLeftDoor = *ActorItr;
		}
		else if (ActorItr->ActorHasTag("CaveGateRight"))
		{
			CaveGateRightDoor = *ActorItr;
		}
	}

	OriginalRotation = TargetRotation = GetActorRotation();
	if (RotateCurve)
	{		
		FOnTimelineFloat RotateFunction;

		RotateFunction.BindUFunction(this, FName("RotateLever"));

		RotateLeverTimeline->AddInterpFloat(RotateCurve, RotateFunction);
		RotateLeverTimeline->SetLooping(false);
		TargetRotation.Pitch += MaxRotation;
	}
}

void ALever::InteractWithObject()
{
	if (!RotateLeverTimeline->IsPlaying())
	{
		if (!bOpen)
		{
			RotateLeverTimeline->ReverseFromEnd();			
			CaveGateRightDoor->InteractWithObject();
			CaveGateLeftDoor->InteractWithObject();
			bOpen = true;
		}
	}	
}

void ALever::RotateLever(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Opening Gates!");
	FRotator NewRotation = FMath::Lerp(OriginalRotation, TargetRotation, Value);
	this->SetActorRotation(NewRotation);
}
