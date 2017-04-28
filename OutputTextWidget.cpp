// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "ProphecyCharacter.h"
#include "OutputTextWidget.h"

void UOutputTextWidget::AddTextToUI(FText NewText)
{		
	//If this item is not already contained in the array add it.	
	if(!TextIsInArray(NewText))
	{
		TextToAdd.Emplace(NewText);
		AddTextToUI();
	}
	
	
}

void UOutputTextWidget::AddInfoTextToUI(FText NewText)
{
	//If this item is not already contained in the array add it.	
	if (!TextIsInArray(NewText))
	{
		InfoTextToAdd.Emplace(NewText);
		AddInfoTextToUI();
	}
}

bool UOutputTextWidget::TextIsInArray(FText TextToFind)
{
	for (int i = 0; i < TextToAdd.Num(); i++)
	{
		if (TextToAdd[i].ToString() == TextToFind.ToString())
		{
			return true;
		}
	}	
	return false;
}

void UOutputTextWidget::GameHasStarted()
{
	AProphecyCharacter* player = Cast<AProphecyCharacter>(this->GetOwningPlayerPawn());
	player->GameHasStarted();
}

void UOutputTextWidget::InitiateHideUI()
{
	HideUI();
}

void UOutputTextWidget::InitiateShowUI()
{
	ShowUI();
}

void UOutputTextWidget::InitiateShowIntroText()
{
	ShowIntroText();
}

void UOutputTextWidget::InitiateHideIntroText()
{
	HideIntroText();
}

void UOutputTextWidget::SetUIHealth(float newPlayerHealth)
{
	playerHealth = newPlayerHealth;
	UpdateUIHealth();
}