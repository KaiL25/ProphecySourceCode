// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "ProphecyGameInstance.generated.h"

class ACheckpoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLanguageChange, FString, language);
/**
 * 
 */
UCLASS()
class PROPHECY_API UProphecyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	

	//The array has the size of the checkpoints in game and should only contain one active checkpoint at a time.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProphecyGameInstance")
	TArray<bool> activeCheckpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProphecyGameInstance")
	int activeShadowsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProphecyGameInstance")
	int activeTexturesButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProphecyGameInstance")
	int activeEffectsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProphecyGameInstance")
	int activeViewDistanceButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProphecyGameInstance")
	int activeAntiAliasingButton;

	UFUNCTION(BlueprintCallable, Category = "ProphecyGameInstance")
	void SetActiveButton(FString lineName, int newActiveButton);

	UFUNCTION(BlueprintCallable, Category = "ProphecyGameInstance")
	int GetActiveButton(FString lineName);

	UFUNCTION(BlueprintCallable, Category = "ProphecyGameInstance")
	int GetCurrentLanguageSetting();
		


	//Returns whether the prophecy level was opened from the main menu or not.
	bool IsOpeningFromMainMenu();
	void SetOpeningFromMainMenu(bool Status);
	void SetCheckpointActive(int CheckpointIndex);
	int GetCurrentCheckpoint();

	void SetCurrentClue(FText newCurrentClue);
	FText GetCurrentClue();
	void ChangeLocalization(FString target);
	FString GetLocalization();
	

private:

	UProphecyGameInstance();
	
	

	//This variable determines whether the intro cutscene gets played or not.
	//If the player comes from the main menu and presses play we want to play the intro cutscene
	//If the player just opens the prophecy level we do not want to play the intro cutscene.
	UPROPERTY(VisibleAnywhere, Category = "ProphecyGameInstance")
	bool bOpeningFromMainMenu;

	UPROPERTY(EditAnywhere, Category = "ProphecyGameInstance")
	int deaths;

	UPROPERTY(VisibleAnywhere, Category = "ProphecyGameInstance")
	int currentCheckpointIndex;
	
	UPROPERTY(VisibleAnywhere, Category = "ProphecyGameInstance")
	FText currentClue = NSLOCTEXT("Normal", "currentClue", "The village seems very quiet,\nmaybe someone in the guesthouse\n can help me.");

	UPROPERTY(VisibleAnywhere, Category = "ProphecyGameInstance")
	FString currentLocalization = "en";
		
	void SetLocalization(FString target);

	FOnLanguageChange LanguageChangeDelegate;
	
	
	
};
