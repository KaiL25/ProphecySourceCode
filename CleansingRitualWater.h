// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CleansingRitualWater.generated.h"

UCLASS()
class PROPHECY_API ACleansingRitualWater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACleansingRitualWater();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void RaiseWaterLevel();	

private:

	UPROPERTY(EditAnywhere, Category = "SecretDoor")
	UStaticMeshComponent* water;

	UPROPERTY(EditAnywhere, Category = "SecretDoor")
	int32 maxDisplacement;

	/**This boxCollider is used to make the player unequip the torch in water*/
	UPROPERTY(VisibleAnywhere, Category = "StatueBoard")
	UBoxComponent* waterTrigger;

	bool bRaised;

	/**Curve reference*/
	UPROPERTY(EditAnywhere, Category = "SecretDoor")
	UCurveFloat* raiseCurve;

	/**Timeline to push the sign in*/
	class UTimelineComponent* raiseTimeline;

	FVector originalLocation;

	FVector targetLocation;	

	UFUNCTION()
	void Raise(float Value);

	UFUNCTION()
	void OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);

	UFUNCTION()
	void OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex);


	
	
};
