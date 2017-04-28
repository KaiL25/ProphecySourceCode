// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "PauseMenuWidget.h"


void UPauseMenuWidget::SetGameInstance(UProphecyGameInstance* NewProphecyGameInstance)
{
	prophecyGameInstance = NewProphecyGameInstance;
}


void UPauseMenuWidget::ChangeLocalization(FString target)
{
	prophecyGameInstance->ChangeLocalization(target);
}
