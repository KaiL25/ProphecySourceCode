// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetGameInstance(UProphecyGameInstance* NewProphecyGameInstance);

	/* Change Localization at Runtime. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Change Localization"), Category = "PauseMenu")
	void ChangeLocalization(FString target);


private:
	UPROPERTY()
	UProphecyGameInstance* prophecyGameInstance;
};
