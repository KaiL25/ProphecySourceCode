// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Signboard.generated.h"

class AProphecyCharacter;

UCLASS()
class PROPHECY_API ASignboard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignboard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	UPROPERTY(EditAnywhere, Category = Signboard)
	UStaticMeshComponent* Board;
	UPROPERTY(EditAnywhere, Category = Signboard)
	UBoxComponent* BoxCollision;
	
	FText runesMessage = NSLOCTEXT("Normal", "runesMessage", "What are these runes?\n Is this the work of a heretic?");

	/*This variable is used to only print out the message on screen once.*/
	bool bHasBeenPrintedToScreen;

	UFUNCTION()
	void OnPlayerEnterBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
	UFUNCTION()
	void OnPlayerExitBoxCollider(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex);
	
	void SetPlayerCanInteractWithPaintingSigns(AProphecyCharacter* NewPlayerCharacter, bool NewStatus);


};
