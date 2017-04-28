// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EventTrigger.generated.h"

class AProphecyCharacter;

UCLASS()
class PROPHECY_API AEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventTrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	virtual void StartEvent();
	virtual void StartEvent(AProphecyCharacter* Player);
	/*Whether the event has been fired or not.
	If implemented in the child, it makes sure that the event can only play once.*/	
	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	bool triggered;

	//This variable is used if the eventTrigger is supposed to activate after the player has done something.
	//It is set to true by default, because most event triggers in the game do not require activation.
	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	bool bActive;
	
	UFUNCTION()
	virtual void ActivateTrigger();

private:	

	UPROPERTY(EditAnywhere, Category = "Trigger")
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
		
};
