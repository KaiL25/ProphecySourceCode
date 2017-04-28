// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SecretDoor.generated.h"

UCLASS()
class PROPHECY_API ASecretDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecretDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void OpenSecretDoor();
	void CloseSecretDoor();

private:

	UPROPERTY(EditAnywhere, Category = "SecretDoor")
    UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, Category = "SecretDoor")
	UAudioComponent* slidingSound;

	UPROPERTY(EditAnywhere, Category = "SecretDoor")
	int32 MaxDisplacement;

	bool bOpen;

	/**Curve reference*/
	UPROPERTY(EditAnywhere, Category = "SecretDoor")
		UCurveFloat* OpenCurve;

	/**Timeline to push the sign in*/
	class UTimelineComponent* OpenDoorTimeline;

	FVector OriginalLocation;

	FVector TargetLocation;

	UParticleSystemComponent* LeftSmoke;
	UParticleSystemComponent* RightSmoke;

	UFUNCTION()
		void Open(float Value);

	
};
