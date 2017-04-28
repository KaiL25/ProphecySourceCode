// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


class UProphecyGameInstance;
/**
 * 
 */
UCLASS()
class PROPHECY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()	

public:
	
	void SetGameInstance(UProphecyGameInstance* NewProphecyGameInstance);

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void PressedStart();

	/* Change Localization at Runtime. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Change Localization"), Category = "MainMenu")
	void ChangeLocalization(FString target);


private:
	UPROPERTY()
	UProphecyGameInstance* prophecyGameInstance;
};
