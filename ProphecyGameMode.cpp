// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Prophecy.h"
#include "ProphecyGameMode.h"
#include "ProphecyHUD.h"
#include "ProphecyCharacter.h"
#include "ProphecyPlayerController.h"
#include "SignLetter.h"
#include "Painting.h"
#include "PaintingPuzzleSign.h"
#include "SecretDoor.h"
#include "SpawnPoint.h"
#include "InnLetter.h"
#include "OutputTextWidget.h"
#include <time.h>  
#include "TextTrigger.h"
#include "EventTrigger.h"
#include "ProphecyGameInstance.h"
#include "Engine.h"
#include "EngineUtils.h"


AProphecyGameMode::AProphecyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Class'/Script/Prophecy.ProphecyCharacter'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;		
	// use our custom HUD class
	HUDClass = AProphecyHUD::StaticClass();
	srand(time(NULL));	
	
}

void AProphecyGameMode::BeginPlay()
{
	prophecyGameInstance = Cast<UProphecyGameInstance>(GetGameInstance());
	CurrentWorld = GetWorld();
	if (CurrentWorld->GetName().Contains("Prophecy"))
	{
		for (TActorIterator<AProphecyCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			if (ActorItr->ActorHasTag("Player"))
			{
				player = *ActorItr;				
			}
		}	

		for (TActorIterator<ATextTrigger> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			if (ActorItr->GetName().Contains("PaintingTextTrigger"))
			{
				paintingTextTriggers.Add(*ActorItr);
			}
		}
		playerController = Cast<AProphecyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

		GenerateLetterSignNumber();
		AssignLetters();
		SetLetterSignNumber();
		GeneratePaintingMaterialIndex();
		AssignPaintings();
		SetPaintingMaterialIndex();
		AssignPaintingPuzzleSigns();
		PreparePaintingSignsForPuzzle();
		AssignSecretDoors();
		AssignSpawnPoints();
		SetInnLetterLocation();
		
		FInternationalization::Get().SetCurrentCulture(prophecyGameInstance->GetLocalization());
		//If the player opened the prophecy level from the main menu play the intro cutscene
		if (prophecyGameInstance->IsOpeningFromMainMenu())
		{
			StartCutscene();
			prophecyGameInstance->SetOpeningFromMainMenu(false);
		}
		else
		{
			player->GameHasStarted();
		}
		//if (textWidgetBP)
		//{
		//	textWidget = CreateWidget<UOutputTextWidget>(this, TextWidgetBP);
		//	textWidget->AddToViewport();
		//}
	}
}

//void AProphecyGameModeUpdateText(FText NewText)
//{
//
//}

void AProphecyGameMode::StartCutscene()
{	
	PlayIntroCutscene();
	playerController->ShowIntroText();	
}

void AProphecyGameMode::PlayOutroCutsceneMessage()
{
	PlayOutroCutscene();
	player->HideSword();
	player->HideTorch();
	//player->SetActorLocation(FVector(0,0,0));	
}

void AProphecyGameMode::CutsceneStarting()
{
	player->DisableInputCutscene();
	//player->DisableInput(Cast<AProphecyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld())));	
	playerController->HideUI();
	player->HideSword();
	player->HideTorch();
}

void AProphecyGameMode::CutsceneEnding()
{	
	player->EnableInputCutscene();
	//player->EnableInput(Cast<AProphecyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld())));
	playerController->ShowUI();
	player->ShowSword();
	player->ShowTorch();
	
}

void AProphecyGameMode::SetGamePaused()
{
	AProphecyPlayerController* const playerController = Cast<AProphecyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (player != NULL)
	{
		if (!bGamePaused)
		{
			bGamePaused = true;
			playerController->SetPause(true);			
		}
		else
		{
			bGamePaused = false;
			playerController->SetPause(false);
		}
	}
}

void AProphecyGameMode::GenerateLetterSignNumber()
{
	Letter01RandomNumber = rand() % 3 + 1;
	Letter02RandomNumber = rand() % 3 + 1;
	while (Letter02RandomNumber == Letter01RandomNumber)
	{
		Letter02RandomNumber = rand() % 3 + 1;
	}
	Letter03RandomNumber = rand() % 3 + 1;
	while (Letter03RandomNumber == Letter02RandomNumber || Letter03RandomNumber == Letter01RandomNumber)
	{
		Letter03RandomNumber = rand() % 3 + 1;
	}	
}

void AProphecyGameMode::AssignLetters()
{		
	for (TActorIterator<ASignLetter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{		
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("Letter01"))
		{
			Letter01 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("Letter02"))
		{
			Letter02 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("Letter03"))
		{
			Letter03 = *ActorItr;			
		}
	}

	for (TActorIterator<AInnLetter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("InnLetter"))
		{
			InnLetter = *ActorItr;
		}	
	}
}

void AProphecyGameMode::SetLetterSignNumber()
{
	prophecyGameInstance = Cast<UProphecyGameInstance>(GetGameInstance());	
	if (prophecyGameInstance->GetLocalization() == "en")
	{
		Letter01->SetMaterialIndex(Letter01RandomNumber);
		Letter02->SetMaterialIndex(Letter02RandomNumber);
		Letter03->SetMaterialIndex(Letter03RandomNumber);
	}
	else
	{
		Letter01->SetMaterialIndex(Letter01RandomNumber, 'j');
		Letter02->SetMaterialIndex(Letter02RandomNumber, 'j');
		Letter03->SetMaterialIndex(Letter03RandomNumber, 'j');
	}
}

void AProphecyGameMode::GeneratePaintingMaterialIndex()
{
	Painting01MaterialIndex = rand() % 2;
	Painting02MaterialIndex = rand() % 2 + 2;
	Painting03MaterialIndex = rand() % 2 + 4;
}

void AProphecyGameMode::AssignPaintings()
{
	for (TActorIterator<APainting> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{

		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("Painting01"))
		{
			Painting01 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("Painting02"))
		{
			Painting02 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("Painting03"))
		{
			Painting03 = *ActorItr;
		}
	}
}

void AProphecyGameMode::SetPaintingMaterialIndex()
{	
	Painting01->SetPaintingMaterial(Painting01MaterialIndex);
	Painting02->SetPaintingMaterial(Painting02MaterialIndex);
	Painting03->SetPaintingMaterial(Painting03MaterialIndex);
}

void AProphecyGameMode::AssignPaintingPuzzleSigns()
{
	for (TActorIterator<APaintingPuzzleSign> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{

		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("PaintingPuzzleSign0"))
		{
			Sign00 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("PaintingPuzzleSign1"))
		{
			Sign01 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("PaintingPuzzleSign2"))
		{
			Sign02 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("PaintingPuzzleSign3"))
		{
			Sign03 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("PaintingPuzzleSign4"))
		{
			Sign04 = *ActorItr;
		}

		else if (ActorItr->ActorHasTag("PaintingPuzzleSign5"))
		{
			Sign05 = *ActorItr;
		}
	}
}

void AProphecyGameMode::PreparePaintingSignsForPuzzle()
{
	if (Painting01MaterialIndex == 0)
	{
		Sign00->SetActive(true);
		Sign00->SetOrderNumber(Letter01->GetMaterialIndex());
	}

	else if (Painting01MaterialIndex == 1)
	{
		Sign01->SetActive(true);
		Sign01->SetOrderNumber(Letter01->GetMaterialIndex());
	}

	if (Painting02MaterialIndex == 2)
	{
		Sign02->SetActive(true);
		Sign02->SetOrderNumber(Letter02->GetMaterialIndex());
	}

	else if (Painting02MaterialIndex == 3)
	{
		Sign03->SetActive(true);
		Sign03->SetOrderNumber(Letter02->GetMaterialIndex());
	}

	if (Painting03MaterialIndex == 4)
	{
		Sign04->SetActive(true);
		Sign04->SetOrderNumber(Letter03->GetMaterialIndex());
	}

	else if(Painting03MaterialIndex == 5)
	{
		Sign05->SetActive(true);
		Sign05->SetOrderNumber(Letter03->GetMaterialIndex());
	}
}

void AProphecyGameMode::PlayerTryingToPressInSign(APaintingPuzzleSign* NewPuzzleSign)
{
	/**If the puzzle is not yet over*/
	if (!bThirdSignPushedIn)
	{
		/**If the player has pressed e on the first sign and it isn't yet pushed in, push it in*/
		if (NewPuzzleSign->GetOrderNumber() == 1 && !NewPuzzleSign->IsPushedIn())
		{
			NewPuzzleSign->PushIn();
			bFirstSignPushedIn = true;
		}

		/**If the player has pressed e on the second sign, it isn't yet pushed in and the first sign is pushed in, push it in*/
		else if (NewPuzzleSign->GetOrderNumber() == 2 && !NewPuzzleSign->IsPushedIn() && bFirstSignPushedIn)
		{
			NewPuzzleSign->PushIn();
			bSecondSignPushedIn = true;
		}

		/**If the player has pressed e on the third sign, it isn't yet pushed in and the second sign is pushed in, push it in*/
		else if (NewPuzzleSign->GetOrderNumber() == 3 && !NewPuzzleSign->IsPushedIn() && bSecondSignPushedIn)
		{
			NewPuzzleSign->PushIn();
			bThirdSignPushedIn = true;
			player->AddTextToUI(kitchenPuzzleSolvedMessage);
			VillageSecretDoor->OpenSecretDoor();
		}

		/**Else the player has pressed e on a sign that is not on the portrait, or the correct order. Push all correct signs out again.*/
		else 
		{
			if (Sign00->IsPushedIn())
			{
				Sign00->PushOut();
			}

			if (Sign01->IsPushedIn())
			{
				Sign01->PushOut();
			}

			if (Sign02->IsPushedIn())
			{
				Sign02->PushOut();
			}

			if (Sign03->IsPushedIn())
			{
				Sign03->PushOut();
			}

			if (Sign04->IsPushedIn())
			{
				Sign04->PushOut();
			}

			if (Sign05->IsPushedIn())
			{
				Sign05->PushOut();
			}
			bFirstSignPushedIn = false;
			bSecondSignPushedIn = false;
			bThirdSignPushedIn = false;
		}
	}
}

void AProphecyGameMode::AssignSecretDoors()
{
	for (TActorIterator<ASecretDoor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->ActorHasTag("VillageSecretDoor"))
		{
			VillageSecretDoor = *ActorItr;
		}
	}
}

void AProphecyGameMode::AssignSpawnPoints()
{
	for (TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SpawnPoints.Add(*ActorItr);
	}
}

void AProphecyGameMode::SetInnLetterLocation()
{
   uint8 InnLetterSpawnPointIndex = rand() % 3;
   if (SpawnPoints[InnLetterSpawnPointIndex])
   {
	   InnLetter->SetActorLocation(SpawnPoints[InnLetterSpawnPointIndex]->GetActorLocation());
   }   
}

void AProphecyGameMode::ALetterWasRead(FString letterName)
{	
	if (letterName == "TraitorsLetter")
	{
		for (int i = 0; i < paintingTextTriggers.Num(); i++)
		{
			paintingTextTriggers[i]->ActivateTrigger();
		}
	}
}
