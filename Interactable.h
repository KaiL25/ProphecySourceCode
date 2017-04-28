// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class AProphecyCharacter;

UCLASS()
class PROPHECY_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void InteractWithObject();

protected:

	UPROPERTY(EditAnywhere, Category = "Interactable")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Interactable")
		AProphecyCharacter* CurrentPlayer;

private:

	

	UPROPERTY(EditAnywhere, Category = "Interactable")
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);

	UFUNCTION()
	void OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex);

	void SetPlayerCanInteractWithObject(AProphecyCharacter* NewPlayerCharacter, bool NewStatus);
	
	

	
};
