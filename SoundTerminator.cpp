// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "SoundTerminator.h"
#include "SoundArea.h"

// Sets default values
ASoundTerminator::ASoundTerminator()
{ 		
	icon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
	soundTerminatorArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SoundTerminatorArea"));
	soundTerminatorArea->bGenerateOverlapEvents = true;
	soundTerminatorArea->OnComponentBeginOverlap.AddDynamic(this, &ASoundTerminator::OnPlayerEnterBoxCollider);
	icon->RelativeLocation = FVector(0, 0, 0);

}

// Called when the game starts or when spawned
void ASoundTerminator::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASoundTerminator::OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	for (int i = 0; i < soundAreaReferences.Max()-1; i++)
	{
		if (soundAreaReferences[i] != NULL)
		{
			soundAreaReferences[i]->StopSound();
		}
	}
	
}
