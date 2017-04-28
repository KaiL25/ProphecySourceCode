// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Painting.generated.h"

UCLASS()
class PROPHECY_API APainting : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APainting();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/**One of the materials for the paintings*/
	UPROPERTY(EditAnywhere, Category = "Painting")
		UMaterial* Material01;

	/**One of the materials for the paintings*/
	UPROPERTY(EditAnywhere, Category = "Painting")
		UMaterial* Material02;

	/**Gets called by the gameMode. Sets the material for the painting according to its index and painting name*/
	void SetPaintingMaterial(uint8 NewMaterialIndex);

private:

	
	/**The 3D model of the painting*/
	UStaticMeshComponent* Painting;

	uint8 TextureIndex;
	uint8 OrderNumber;
	
	
	
	
	
};
