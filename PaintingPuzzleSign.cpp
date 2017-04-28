// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "PaintingPuzzleSign.h"
#include "Engine.h"


// Sets default values
APaintingPuzzleSign::APaintingPuzzleSign()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
	Sign = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sign"));	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));	
	bActive = false;
	bInteractable = false;
	bSignOrderNumber = false;
	this->Tags.Add("PaintingPuzzleSign");
	PushInTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenDoorTimeline"));	
}

// Called when the game starts or when spawned
void APaintingPuzzleSign::BeginPlay()
{
	Super::BeginPlay();
	if (this->ActorHasTag("PaintingPuzzleSign0"))
	{
		SignIndex = 0;
	}
	else if (this->ActorHasTag("PaintingPuzzleSign1"))
	{
		SignIndex = 1;
	}

	else if (this->ActorHasTag("PaintingPuzzleSign2"))
	{
		SignIndex = 2;
	}

	else if (this->ActorHasTag("PaintingPuzzleSign3"))
	{
		SignIndex = 3;
	}

	else if (this->ActorHasTag("PaintingPuzzleSign4"))
	{
		SignIndex = 4;
	}

	else if (this->ActorHasTag("PaintingPuzzleSign5"))
	{
		SignIndex = 5;
	}

	OriginalLocation = TargetLocation = GetActorLocation();
	if (PushInCurve)
	{
		FOnTimelineFloat PushInFunction;

		PushInFunction.BindUFunction(this, FName("PushIn"));

		PushInTimeline->AddInterpFloat(PushInCurve, PushInFunction);
		PushInTimeline->SetLooping(false);
		TargetLocation.Y += MaxDisplacement;
	}	
}

void APaintingPuzzleSign::PushIn(float Value)
{
	FVector NewVector = FMath::Lerp(OriginalLocation, TargetLocation, Value);

	this->SetActorRelativeLocation(NewVector);
}

void APaintingPuzzleSign::SetActive(bool NewStatus)
{
	bActive = NewStatus;
}

void APaintingPuzzleSign::SetOrderNumber(uint8 NewOrderNumber)
{
	OrderNumber = NewOrderNumber;
}

// Called every frame
void APaintingPuzzleSign::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APaintingPuzzleSign::PushIn()
{
	if (bActive)
	{
		/**If the sign is not currently pushing in, or out*/
		if (!PushInTimeline->IsPlaying())
		{
			if (!bSignPushed)
			{
				PushInTimeline->PlayFromStart();
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Pushing in!");
				bSignPushed = true;
			}
			
		}		
	}	
}

void APaintingPuzzleSign::PushOut()
{
	/**If the sign is not currently pushing in, or out*/
	if (!PushInTimeline->IsPlaying())
	{
		if(bSignPushed)
		{
			PushInTimeline->ReverseFromEnd();
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Pushing out!");
			bSignPushed = false;
		}
	}
}

bool APaintingPuzzleSign::IsActive()
{
	return bActive;
}

bool APaintingPuzzleSign::IsPushedIn()
{
	return bSignPushed;
}

int APaintingPuzzleSign::GetOrderNumber()
{
	return OrderNumber;
}

void  APaintingPuzzleSign::ActivateOutline()
{
	Sign->SetRenderCustomDepth(true);	
}

void  APaintingPuzzleSign::DeactivateOutline()
{	
	Sign->SetRenderCustomDepth(false);
}