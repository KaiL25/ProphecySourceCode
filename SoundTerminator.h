// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SoundTerminator.generated.h"

class ASoundArea;

UCLASS()
class PROPHECY_API ASoundTerminator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundTerminator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

private:

	UPROPERTY(EditAnywhere, Category = "SoundTerminator")
	UBillboardComponent * icon;

	UPROPERTY(EditAnywhere, Category = "SoundTerminator")
	UBoxComponent* soundTerminatorArea;

	/**These references are the sound areas in the level.
	   The way the level is set up demands several sound area references*/
	UPROPERTY(EditAnywhere, Category = "SoundTerminator")
	TArray<ASoundArea*> soundAreaReferences;	

	UFUNCTION()
	void OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
	
};
