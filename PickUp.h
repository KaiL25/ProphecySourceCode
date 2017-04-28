// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

class AProphecyCharacter;

UCLASS()
class PROPHECY_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FVector GetOriginalLocation();
	FRotator GetOriginalRotation();
	bool IsCollectable();

	/**Sets the player's corresponding bool to true*/
	virtual APickUp* GetCollectable();
	uint8 GetCollectableIndex();

	/**The axis around which the object rotates when being examined*/
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	UStaticMeshComponent * axis;

	

protected:

	UPROPERTY(EditAnywhere, Category = "Pick Up")
	UStaticMeshComponent* mesh;

private:

	/**Determines whether the object will be put back down after looking at it,
	or if it will be added to the inventory*/
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	bool bCollectable;
	
	/**This index helps the player class idenfity what item was picked up
	   The index corresponds with a certain pick up bool on the player*/
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	uint8 collectableIndex;

	/**The objects original position. This is where the object returns to if it is not collectable.*/
	UPROPERTY(VisibleAnywhere, Category = "Pick Up")
	FVector originalLocation;
	
	UPROPERTY(VisibleAnywhere, Category = "Pick Up")
	FRotator originalRotation;

	/*The area in which the player can pick up the object*/
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	UBoxComponent* pickUpArea;	

	UFUNCTION()
	void OnPlayerEnterPickUpArea(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
	
	UFUNCTION()
	void OnPlayerExitPickUpArea(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex);

	void SetPlayerCanPickUpObject(AProphecyCharacter* NewPlayerCharacter, bool NewStatus);	
};
