// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "InnLetter.generated.h"


/**
 * 
 */
UCLASS()
class PROPHECY_API AInnLetter : public APickUp
{
	GENERATED_BODY()


public:

	UFUNCTION()
	void TheLetterWasRead();

	UFUNCTION()
	void ChangeLanguage(FString newLanguage);

private:

	AInnLetter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Set to true when the player picks up the letter for the first time.
	//Used to avoid calling the gameController's aLetterWasRead function every time the player picks up the letter.
	bool bLetterRead;

	UPROPERTY(EditAnywhere, Category = "InnLetter")
	UMaterial* letterMatEn;

	UPROPERTY(EditAnywhere, Category = "InnLetter")
	UMaterial* letterMatJp;

	UPROPERTY()
	UProphecyGameInstance* prophecyGameInstance;
	
	
};
