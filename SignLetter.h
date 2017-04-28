// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "SignLetter.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API ASignLetter : public APickUp
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASignLetter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	/**Sets the letter's material index*/
	void SetMaterialIndex(int newIndex, char language = 'e');

	/**Returns the material index set for the letter. Gets called by gamecontroller in order to assign the correct order number to the active signs.*/
	uint8 GetMaterialIndex();

private:

	/**The letter's 3D Model.*/
	UPROPERTY(VisibleAnywhere, Category = "Sign Letter")
	UStaticMeshComponent* Letter;

	/**Determines the material the letter has.*/
	UPROPERTY(VisibleAnywhere, Category = "Sign Letter")
	uint8 MaterialIndex;

	/**One of the materials for the sign letters*/
	UPROPERTY(EditAnywhere, Category = "SignLetter")
	UMaterial* Material01;

	UPROPERTY(EditAnywhere, Category = "SignLetter")
	UMaterial* Material01_Jp;

	/**One of the materials for the sign letters*/
	UPROPERTY(EditAnywhere, Category = "SignLetter")
	UMaterial* Material02;

	UPROPERTY(EditAnywhere, Category = "SignLetter")
	UMaterial* Material02_Jp;

	/**One of the materials for the sign letters*/
	UPROPERTY(EditAnywhere, Category = "SignLetter")
	UMaterial* Material03;

	UPROPERTY(EditAnywhere, Category = "SignLetter")
	UMaterial* Material03_Jp;

	/**Sets the Letter's texture according to the TextureIndex assigned by the ProphecyGameMode*/
	void SetMaterial(char language = 'e');	
};

	
	

