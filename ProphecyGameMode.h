// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "ProphecyGameMode.generated.h"

class ASignLetter;
class APainting;
class APaintingPuzzleSign;
class ASecretDoor;
class ASpawnPoint;
class AProphecyCharacter;
class AInnLetter;
class UProphecyGameInstance;
class ATextTrigger;
class UOutputTextWidget;


UCLASS(minimalapi)
class AProphecyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProphecyGameMode();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOutputTextWidget> textWidgetBP;

	void PlayerTryingToPressInSign(APaintingPuzzleSign* NewPuzzleSign);

	UFUNCTION()
	void SetGamePaused();

	UFUNCTION(BlueprintImplementableEvent, Category = "Prophecy")
	void PlayIntroCutscene();

	UFUNCTION(BlueprintImplementableEvent, Category = "Prophecy")
	void PlayRitualRoomCutscene();

	UFUNCTION(BlueprintImplementableEvent, Category = "Prophecy")
	void PlayOutroCutscene();

	UFUNCTION(BlueprintImplementableEvent, Category = "Prophecy")
	void SkipCutscene();

	UFUNCTION()
	void PlayOutroCutsceneMessage();

	UFUNCTION(BlueprintCallable, Category = "Prophecy")
	void CutsceneStarting();

	UFUNCTION(BlueprintCallable, Category = "Prophecy")
	void CutsceneEnding();

	UFUNCTION()
	void ALetterWasRead(FString letterName);

private:
	
	/*Designates whether the game is paused or not.*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	bool bGamePaused;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	UProphecyGameInstance* prophecyGameInstance;

	/*The reference to the player.*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	AProphecyCharacter* player;	

	UPROPERTY()
	class AProphecyPlayerController* playerController;

	FText kitchenPuzzleSolvedMessage = NSLOCTEXT("Normal", "kitchenPuzzleSolvedMessage", "I heard a noise outside.\n I must have set something in motion.");

	/**The random number which determines the text the letter receives*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	uint8 Letter01RandomNumber;

	/**The random number which determines the text the letter receives*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	uint8 Letter02RandomNumber;

	/**The random number which determines the text the letter receives*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	uint8 Letter03RandomNumber;

	/**One of the letters that give the player a hint about the order of the sign puzzle*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	ASignLetter* Letter01;

	/**One of the letters that give the player a hint about the order of the sign puzzle*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	ASignLetter* Letter02;

	/**One of the letters that give the player a hint about the order of the sign puzzle*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	ASignLetter* Letter03;

	/**The index that determines the material on painting 01*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	uint8 Painting01MaterialIndex;

	/**The index that determines the material on painting 02*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	uint8 Painting02MaterialIndex;

	/**The index that determines the material on painting 03*/
	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	uint8 Painting03MaterialIndex;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APainting* Painting01;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APainting* Painting02;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APainting* Painting03;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APaintingPuzzleSign* Sign00;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APaintingPuzzleSign* Sign01;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APaintingPuzzleSign* Sign02;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APaintingPuzzleSign* Sign03;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APaintingPuzzleSign* Sign04;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	APaintingPuzzleSign* Sign05;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	TArray<ATextTrigger*> paintingTextTriggers;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	bool bFirstSignPushedIn;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	bool bSecondSignPushedIn;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	bool bThirdSignPushedIn;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	UWorld* CurrentWorld;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	ASecretDoor* VillageSecretDoor;

	UPROPERTY(EditAnywhere, Category = "Prophecy")
	TArray<ASpawnPoint*> SpawnPoints;

	UPROPERTY(VisibleAnywhere, Category = "Prophecy")
	AInnLetter* InnLetter;	

	void BeginPlay();
	
	void StartCutscene();

	/**Generates the random numbers and sets the variables which determine the text the letter receives*/
	void GenerateLetterSignNumber();

	/**Assigns the previously generated random number to the letter*/
	void SetLetterSignNumber();

	/**Assigns the Letters in the scene to the ASignLetter variables*/
	void AssignLetters();

	/**Sets the painting material index according to the painting's name*/
	void GeneratePaintingMaterialIndex();

	/**Gets the three paintings from world and assigns them to the variables*/
	void AssignPaintings();

	/**Sets the painting material according to the painting's name in the painting class*/
	void SetPaintingMaterialIndex();

	/**Gets the six painting puzzle signs from world and assigns them to the variables*/
	void AssignPaintingPuzzleSigns();

	/**Activates the signs that are used for the puzzle this time and sets their order number*/
	void PreparePaintingSignsForPuzzle();
	
	/**Gets the secret doors in the world and assigns them to the variables*/
	void AssignSecretDoors();

	/**Gets the spawn points in the scene and assigns them to the spawnpoints array*/
	void AssignSpawnPoints();

	/**Gets a random spawn point in the inn and sets the inn letter's location to it*/
	void SetInnLetterLocation();
};



