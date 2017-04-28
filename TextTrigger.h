// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EventTrigger.h"
#include "TextTrigger.generated.h"


class AProphecyCharacter;
/**
 * 
 */
UCLASS()
class PROPHECY_API ATextTrigger : public AEventTrigger
{
	GENERATED_BODY()

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "TextTrigger")
	FText sentence1;

	UPROPERTY(EditAnywhere, Category = "TextTrigger")
	FText sentence2;

	UPROPERTY(EditAnywhere, Category = "TextTrigger")
	FText sentence3;

	/*Since new line commands do not work in the editor's string box I had to append the sentences to outputText.
	  outputText is the final output after sentence1, 2 and 3 have been appended with new lines in between.*/
	UPROPERTY(EditAnywhere, Category = "TextTrigger")
	FText outputText;

	/*Determines whether the outputText gets set as a clue for the player to see on pressing j*/
	UPROPERTY(EditAnywhere, Category = "TextTrigger")
	bool bClue;

	/*The clue that gets set if bClue is set to true.*/
	UPROPERTY(EditAnywhere, Category = "TextTrigger")
	FText clue;

	/*Used to determine whether the text gets displayed on screen everytime the player enters the box collider*/
	UPROPERTY(EditAnywhere, Category = "TextTrigger")
	bool bRepeat;

	ATextTrigger();
	virtual void StartEvent(AProphecyCharacter* Player) override;

public:
	UFUNCTION()
	virtual void ActivateTrigger() override;
	
};
