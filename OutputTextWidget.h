// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "OutputTextWidget.generated.h"

/**
 *Followed this tutorial http://orfeasel.com/using-unreal-motion-graphics-umg-with-c/
 */
UCLASS()
class PROPHECY_API UOutputTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/*Responsible for adding the TextToAdd to our UI*/
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void AddTextToUI();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void AddInfoTextToUI();

	UPROPERTY(BlueprintReadOnly)
	float playerHealth;

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> TextToAdd;

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> InfoTextToAdd;

	/*This variable is used to signal when to add the first instruction text to screen 
	  and show the player, since the player is invisible during cutscene.*/
	UFUNCTION(BlueprintCallable, Category = "UI")
	void GameHasStarted();

	void InitiateHideUI();

	void InitiateShowUI();

	void InitiateShowIntroText();

	void InitiateHideIntroText();

public:

	/*Adds the text inside our UI by using our AddTextToUI protected function*/
	void AddTextToUI(FText NewText);

	/*Adds the text inside our UI by using our AddTextToUI protected function*/
	void AddInfoTextToUI(FText NewText);
	
	bool TextIsInArray(FText TextToFind);

	//Hides the UI (Reticle and info text)
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void HideUI();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowUI();

	//Shows the text that appears during the intro cutscene.
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowIntroText();

	//Shows the text that appears during the intro cutscene.
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void HideIntroText();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateUIHealth();


	void SetUIHealth(float newPlayerHealth);
	



	

};
