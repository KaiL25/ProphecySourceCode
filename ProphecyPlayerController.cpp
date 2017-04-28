// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "OutputTextWidget.h"
#include "MainMenuWidget.h"
#include "PauseMenuWidget.h"
#include "ProphecyCharacter.h"
#include "ProphecyGameInstance.h"
#include "ProphecyPlayerController.h"
#include "Checkpoint.h"
#include "Engine.h"

void AProphecyPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	prophecyGameInstance = Cast<UProphecyGameInstance>(GetWorld()->GetGameInstance());
	//prophecyGameInstance = GetWorld()->Get
	if (GetWorld()->GetName().Contains("MainMenu"))
	{
		if (mainMenuWidgetBP)
		{
			mainMenuWidget = CreateWidget<UMainMenuWidget>(this, mainMenuWidgetBP);

			mainMenuWidget->AddToViewport();
			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
			GiveMainMenuGameInstanceReference();
			GivePauseMenuGameInstanceReference();
		}
	}

	else if(GetWorld()->GetName().Contains("Prophecy"))
	{
		for (TActorIterator<ACheckpoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			if (ActorItr->GetName().Contains("Checkpoint"))
			{
				checkpoints.Add(*ActorItr);

			}
		}
		
		//Get the current checkpoint and convert it to a string.
		FString checkpointIndexAsString = FString::FromInt(prophecyGameInstance->GetCurrentCheckpoint());
		for (int i = 0; i < checkpoints.Num(); i++)
		{
			//If the checkpoint at i contains the number of the current checkpoint index in its name...
			if (checkpoints[i]->GetName().Contains(checkpointIndexAsString))
			{
				//Set the player to the checkpoint's location and rotation.
				InPawn->SetActorLocation(checkpoints[i]->GetActorLocation());
				InPawn->SetActorRotation(checkpoints[i]->GetActorRotation());
				//ConsoleCommand
				
			}
		}
		
		if (textWidgetBP)
		{
			//Creating our widget and adding it to our viewport
			textWidget = CreateWidget<UOutputTextWidget>(this, textWidgetBP);

			textWidget->AddToViewport();
		}

		if (pauseMenuWidgetBP)
		{
			pauseMenuWidget = CreateWidget<UPauseMenuWidget>(this, pauseMenuWidgetBP);
		}
		
	}
	
}

void AProphecyPlayerController::UpdateText(FText newText)
{
	AProphecyCharacter* character = Cast<AProphecyCharacter>(GetPawn());

	if (character)
	{
		//Updating our UI with the new collected item
		textWidget->AddTextToUI(newText);
	}
}

void AProphecyPlayerController::UpdateInfoText(FText newText)
{
	AProphecyCharacter* character = Cast<AProphecyCharacter>(GetPawn());

	if (character)
	{
		//Updating our UI with the new info text
		textWidget->AddInfoTextToUI(newText);
	}
}

void AProphecyPlayerController::TogglePauseScreen()
{
	if (!bGamePaused)
	{
		bGamePaused = true;
		pauseMenuWidget->AddToViewport();	
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;

	}
	else
	{
		bGamePaused = false;		
		pauseMenuWidget->RemoveFromParent();
		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;
	}
}

void AProphecyPlayerController::HideUI()
{
	textWidget->HideUI();
}

void AProphecyPlayerController::ShowUI()
{
	textWidget->ShowUI();
}

void AProphecyPlayerController::ShowIntroText()
{
	textWidget->ShowIntroText();
}

void AProphecyPlayerController::HideIntroText()
{
	textWidget->HideIntroText();
}

void AProphecyPlayerController::GiveMainMenuGameInstanceReference()
{
	mainMenuWidget->SetGameInstance(Cast<UProphecyGameInstance>(this->GetGameInstance()));
}

void AProphecyPlayerController::GivePauseMenuGameInstanceReference()
{
	//FIX ME, I CRASH YOUR GAME!!!!!!
	//pauseMenuWidget->SetGameInstance(Cast<UProphecyGameInstance>(this->GetGameInstance()));
}

void AProphecyPlayerController::UpdateUIHealth(float newPlayerHealth)
{
	textWidget->SetUIHealth(newPlayerHealth);
}

