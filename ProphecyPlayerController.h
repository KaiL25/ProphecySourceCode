// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ProphecyPlayerController.generated.h"


class ACheckpoint;
/**
 * 
 */
UCLASS()
class PROPHECY_API AProphecyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	class UProphecyGameInstance* prophecyGameInstance;

	

	/*Our UI Reference*/
	UPROPERTY()
	class UOutputTextWidget* textWidget;

	UPROPERTY()
	class UMainMenuWidget* mainMenuWidget;

	UPROPERTY()
	class UPauseMenuWidget* pauseMenuWidget;

	UPROPERTY()
	int32 tempIndex;

	bool bGamePaused;

	void SortCheckpointArray();

protected:

	//The checkpoints placed throughout the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prophecy Player Controller")
	TArray<ACheckpoint*> checkpoints;

	/*Property which is pointing to our Widget Blueprint in order to instantiate it using c++*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOutputTextWidget> textWidgetBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget> mainMenuWidgetBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPauseMenuWidget> pauseMenuWidgetBP;

public:
	/*Executes when the controller possess a pawn*/
	virtual void Possess(APawn* InPawn) override;

	/*Updates the UI based on the item that the player has collected*/
	void UpdateText(FText NewText);

	void UpdateInfoText(FText NewText);

	

	void TogglePauseScreen();
	
	void HideUI();
	void ShowUI();
	void ShowIntroText();
	void HideIntroText();
	void GiveMainMenuGameInstanceReference();
	void GivePauseMenuGameInstanceReference();
	void UpdateUIHealth(float newPlayerHealth);
	
};
