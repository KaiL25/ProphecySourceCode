// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "InnLetter.h"
#include "ProphecyGameMode.h"
#include "ProphecyGameInstance.h"


AInnLetter::AInnLetter()
{
	letterMatEn = CreateDefaultSubobject<UMaterial>(TEXT("EnglishMat"));
	letterMatJp = CreateDefaultSubobject<UMaterial>(TEXT("JapaneseMat"));
	
}

void AInnLetter::BeginPlay()
{
	Super::BeginPlay();
	prophecyGameInstance = Cast<UProphecyGameInstance>(GetGameInstance());
	
	if (prophecyGameInstance != NULL)
	{
		FString localization = prophecyGameInstance->GetLocalization();
		ChangeLanguage(localization);
	}

}



void AInnLetter::TheLetterWasRead()
{	
	if (!bLetterRead)
	{		
		bLetterRead = true;
		AProphecyGameMode* gameMode = Cast<AProphecyGameMode>(this->GetWorld()->GetAuthGameMode());
		gameMode->ALetterWasRead(this->GetName());
	}	
}

void AInnLetter::ChangeLanguage(FString newLanguage)
{
	if (newLanguage != "en")
	{
		mesh->SetMaterial(0, letterMatJp);
	}
	else
	{
		mesh->SetMaterial(0, letterMatEn);
	}

}
