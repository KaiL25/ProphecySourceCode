// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "ProphecyGameInstance.h"
#include "InnLetter.h"

UProphecyGameInstance::UProphecyGameInstance()
{
	activeCheckpoint.Init(false, 4);
	activeCheckpoint[0] = true;
	activeShadowsButton = 3;
	activeTexturesButton = 3;
	activeEffectsButton = 3;
	activeViewDistanceButton = 3;
	activeAntiAliasingButton = 3;	
	deaths = 0;


}

bool UProphecyGameInstance::IsOpeningFromMainMenu()
{
	return bOpeningFromMainMenu;
}

void UProphecyGameInstance::SetOpeningFromMainMenu(bool Status)
{
	bOpeningFromMainMenu = Status;
}

void UProphecyGameInstance::SetCheckpointActive(int CheckpointIndex)
{
	//If the player has activated a checkpoint that is deeper in the level than the current one...
	if (currentCheckpointIndex < CheckpointIndex)
	{
		//First deactivate all checkpoints in order to make sure there is only one checkpoint active.
		for (int i = 0; i < activeCheckpoint.Num(); i++)
		{
			activeCheckpoint[i] = false;
		}
		//Then set the checkpoint getting passed in to true.
		activeCheckpoint[CheckpointIndex] = true;
	}
}

int UProphecyGameInstance::GetCurrentCheckpoint()
{
	for (int i = 0; i < activeCheckpoint.Num(); i++)
	{
		if (activeCheckpoint[i] == true)
		{
			return i;
		}
	}
	return -1;
}

int UProphecyGameInstance::GetActiveButton(FString lineName)
{
	if (lineName == "Shadows")
	{
		return activeShadowsButton;
	}

	else if (lineName == "Textures")
	{
		return activeTexturesButton;
	}

	else if(lineName == "Effects")
	{
		return activeEffectsButton;
		
	}

	else if (lineName == "ViewDistance")
	{
		return activeViewDistanceButton;
	}

	else
	{
		return activeAntiAliasingButton;
	}
}

void UProphecyGameInstance::SetActiveButton(FString lineName, int newActiveButton)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: lineName: %s, newActiveButton: %d"), lineName, newActiveButton));
	if (lineName == "Shadows")
	{
		activeShadowsButton = newActiveButton;
	}

	else if (lineName == "Textures")
	{
		activeTexturesButton = newActiveButton;
	}

	else if (lineName == "Effects")
	{
		activeEffectsButton = newActiveButton;

	}

	else if (lineName == "ViewDistance")
	{
		activeViewDistanceButton = newActiveButton;
	}

	else
	{
		activeAntiAliasingButton = newActiveButton;
	}
}

void UProphecyGameInstance::SetCurrentClue(FText newCurrentClue)
{
	currentClue = newCurrentClue;
}

FText UProphecyGameInstance::GetCurrentClue()
{
	return currentClue;
}

void UProphecyGameInstance::ChangeLocalization(FString target)
{
	FInternationalization::Get().SetCurrentCulture(target);
	SetLocalization(target);

//	FSharedRef< AInnLetter > innLetter(new AInnLetter());

	
   
	//LanguageChangeDelegate.AddDynamic(this, &AInnLetter::ChangeLanguage);
	//if (LanguageChangeDelegate.IsBound())
	//{
	//	LanguageChangeDelegate.Broadcast(target);
	//}
  
	
		//LanguageChange.Execute(TEXT("target"));
	

}

void UProphecyGameInstance::SetLocalization(FString target)
{
	
	currentLocalization = target;
}

FString UProphecyGameInstance::GetLocalization()
{
	return currentLocalization;
}

int UProphecyGameInstance::GetCurrentLanguageSetting()
{
	if (currentLocalization != "en")
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}