// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FloorSpikes.generated.h"


UCLASS()
class PROPHECY_API AFloorSpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSpikes();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "FloorSpikes")
	UStaticMeshComponent* floor;

	UPROPERTY(VisibleAnywhere, Category = "FloorSpikes")
	UStaticMeshComponent* spikes;

	UPROPERTY(EditAnywhere, Category = "FloorSpikes")
	UBoxComponent* boxTrigger;

	UPROPERTY(EditAnywhere, Category = "FloorSpikes")
	UBoxComponent* killVolume;

	UPROPERTY(EditAnywhere, Category = "FloorSpikes")
	int32 maxDisplacement;

	UPROPERTY(VisibleAnywhere, Category = "FloorSpikes")
	UBillboardComponent* icon;

	UPROPERTY(VisibleAnywhere, Category = "FloorSpikes")
	bool bRaised;

	/**Curve reference*/
	UPROPERTY(EditAnywhere, Category = "FloorSpikes")
	UCurveFloat* raiseCurve;

	/**Timeline to push the sign in*/
	class UTimelineComponent* raiseTimeline;

	FVector originalLocation;

	FVector targetLocation;

	/**Used to raise the spikes when the player enters the box collision*/
	void RaiseSpikes();

	void LowerSpikes();

	/**Needed to bind an animation to the spikes*/
	UFUNCTION()
	void Raise(float Value);
	
	UFUNCTION()
	void OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);

	UFUNCTION()
	void OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void KillPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
};
