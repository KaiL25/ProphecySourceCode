// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "TextTrigger.h"

ATextTrigger::ATextTrigger()
{

}

// Called when the game starts or when spawned
void ATextTrigger::BeginPlay()
{
	Super::BeginPlay();
	if (this->GetName().Contains("PaintingTextTrigger"))
	{
		bActive = false;
	}

}

void ATextTrigger::StartEvent(AProphecyCharacter* Player)
{
	if (bActive)
	{
		if (!triggered)
		{
			FString sentence1String = sentence1.ToString();
			FString sentence2String = sentence2.ToString();
			FString sentence3String = sentence3.ToString();
			FString completeSentence = sentence1String + " " + sentence2String + " " + sentence3String;
			outputText = FText::FromString(completeSentence);
			//FText temp = FText::Format(sentence1, sentence2, sentence3);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Output text: outputText: %s"), outputText));
			Player->AddTextToUI(outputText);
			if (bClue)
			{
				//If the clue is not empty
				if (!clue.IsEmpty())
				{
					Player->SetClue(clue);
				}
				else
				{
					Player->SetClue(outputText);
				}
			}
			if (!bRepeat)
			{
				triggered = true;
			}
		}
	}
}

void ATextTrigger::ActivateTrigger()
{
	bActive = true;
}

