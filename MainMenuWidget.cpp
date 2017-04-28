// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "ProphecyGameInstance.h"
#include "MainMenuWidget.h"

void UMainMenuWidget::SetGameInstance(UProphecyGameInstance* NewProphecyGameInstance)
{
	prophecyGameInstance = NewProphecyGameInstance;
}

void UMainMenuWidget::PressedStart()
{
	prophecyGameInstance->SetOpeningFromMainMenu(true);
}

void UMainMenuWidget::ChangeLocalization(FString target)
{
	prophecyGameInstance->ChangeLocalization(target);
}




