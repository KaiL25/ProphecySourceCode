// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaintingPuzzleSign.generated.h"

UCLASS()
class PROPHECY_API APaintingPuzzleSign : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintingPuzzleSign();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetActive(bool NewStatus);
	void SetOrderNumber(uint8 NewOrderNumber);
	/**This gets called by the ProphecyGameMode when the player pressed e while looking at the puzzle sign.
	   The function checks whether the sign is active and pressed in the right order
	   Calls a move function if active and in the right order.*/
	void PushIn();
	void PushOut();
	/**Checks if the sign is part of the signs used in the paintigns*/
	bool IsActive();
	bool IsPushedIn();
	int GetOrderNumber();

	void ActivateOutline();
	void DeactivateOutline();

private:

	USceneComponent* Root;

	/**The 3D model of the sign*/
	UPROPERTY(EditAnywhere, Category = "PaintingPuzzleSign")
	UStaticMeshComponent* Sign;

	UPROPERTY(VisibleAnywhere, Category = "PaintingPuzzleSign")
	UBoxComponent* BoxCollider;

	/**The unique index that this sign has, which tells us its 3D model*/
	UPROPERTY(VisibleAnywhere, Category = "PaintingPuzzleSign")
	uint8 SignIndex;

	/**If active, the place in the order in which it has to be pushed*/
	UPROPERTY(VisibleAnywhere, Category = "PaintingPuzzleSign")
	uint8 OrderNumber;

	/**Whether the sign is in the painting or not and therefore can be activated*/
	UPROPERTY(VisibleAnywhere, Category = "PaintingPuzzleSign")
	bool bActive;

	/**Whether the sign can be interacted with or not. Used when the sign is moving*/
	bool bInteractable;

	/**Whether the sign is already pushed in or not*/
	bool bSignPushed;

	/**Whether the sign was pushed in the right order*/
	bool bSignOrderNumber;

	UPROPERTY(EditAnywhere, Category = "PaintingPuzzleSign")
	int8 MaxDisplacement;

	/**Curve reference*/
	UPROPERTY(EditAnywhere, Category = "PaintingPuzzleSign")
	UCurveFloat* PushInCurve;	

	/**Timeline to push the sign in*/
	class UTimelineComponent* PushInTimeline;	

	FVector OriginalLocation;

	FVector TargetLocation;

	UFUNCTION()
	void PushIn(float Value);	
};
