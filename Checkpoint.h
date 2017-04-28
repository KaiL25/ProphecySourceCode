// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class PROPHECY_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

private:
	
	//Should be the same as the number in the name in order to correspond with the array indeces.
	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	uint8 checkpointIndex;

	UPROPERTY(VisibleAnywhere, Category = "Checkpoint")
	UBoxComponent* boxCollision;

	UFUNCTION()
	void OnEnterBoxCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
	
};
