// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "SoundArea.h"
#include "Engine.h"


// Sets default values
ASoundArea::ASoundArea()
{ 	
	icon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
	soundArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SoundArea"));
	soundArea->bGenerateOverlapEvents = true;
	soundArea->OnComponentBeginOverlap.AddDynamic(this, &ASoundArea::OnPlayerEnterBoxCollider);	
	sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	sound->bAutoActivate = false;
	icon->SetupAttachment(soundArea);
	icon->RelativeLocation = FVector(0, 0, 0);
	bActive = true;
}

void ASoundArea::SetSoundAreaActive(bool bStatus)
{
	bActive = bStatus;
}

void ASoundArea::OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (bActive)
	{
		if (sound != NULL)
		{
			/**If the player has entered the area and the sound is not already playing...*/
			if (OtherActor->ActorHasTag("Player") && !sound->IsPlaying())
			{
				/**If there is a sisterSoundArea...*/
				if (sisterSoundArea)
				{
					/**If the sisterSoundArea is not already playing the sound*/
					if (!sisterSoundArea->GetIsSoundPlaying())
					{
						sound->FadeIn(1);
					}
				}
				/**If there is no sisterSoundArea...*/
				else
				{
					sound->FadeIn(1);
				}
			}
		}
	}
}

void ASoundArea::StopSound()
{
	if (sound != NULL)
	{
		if (sound->IsPlaying())
		{
			sound->FadeOut(2, 0);
		}
	}
}

bool ASoundArea::GetIsSoundPlaying()
{
	if (sound != NULL)
	{
		if (sound->IsPlaying())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

