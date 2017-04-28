// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SoundArea.generated.h"

UCLASS()
class PROPHECY_API ASoundArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundArea();	

	bool GetIsSoundPlaying();

	void StopSound();

	void SetSoundAreaActive(bool bStatus);

private:

	UPROPERTY(EditAnywhere, Category = "SoundArea")
	UBillboardComponent * icon;

	UPROPERTY(EditAnywhere, Category = "SoundArea")
	UBoxComponent* soundArea;

	UPROPERTY(EditAnywhere, Category = "SoundArea")
	UAudioComponent* sound;

	UPROPERTY(EditAnywhere, Category = "SoundArea")
	bool bActive;

	/*A reference to the sound area that plays the same sound.
	  Used to check whether the same sound is already playing or not.*/
	UPROPERTY(EditAnywhere, Category = "SoundArea")
	ASoundArea* sisterSoundArea;

	UPROPERTY(EditAnywhere, Category = "SoundArea")
	bool bEndPlayOnReenter;
	
	UFUNCTION()
	void OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
};
