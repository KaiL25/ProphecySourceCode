// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "PickUp.h"
#include "SignLetter.h"


// Sets default values
ASignLetter::ASignLetter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Letter = mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_letter(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (StaticMeshOb_letter.Object)
		Letter->SetStaticMesh(StaticMeshOb_letter.Object);
	Letter->SetRelativeScale3D(FVector(.2, .3, 1));
	MaterialIndex = 0;

	//UMaterial> Material_Letter01(TEXT("Material'/Game/Prophecy/Prophecy_Materials/SignOrderLetter01_Mat.SignOrderLetter01_Mat'"));
	//if (Material_Letter01.Succeeded())
	//{
	//	Material01 = Material_Letter01.Object;
	//}
	//
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material_Letter02(TEXT("Material'/Game/Prophecy/Prophecy_Materials/SignOrderLetter02_Mat.SignOrderLetter02_Mat'"));
	//if (Material_Letter02.Succeeded())
	//{
	//	Material02 = Material_Letter02.Object;
	//}
	//
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material_Letter03(TEXT("Material'/Game/Prophecy/Prophecy_Materials/SignOrderLetter03_Mat.SignOrderLetter03_Mat'"));
	//if (Material_Letter03.Succeeded())
	//{
	//	Material03 = Material_Letter03.Object;
	//}
}

// Called when the game starts or when spawned
void ASignLetter::BeginPlay()
{
	Super::BeginPlay();
	

}

void ASignLetter::SetMaterialIndex(int newIndex, char language)
{
	MaterialIndex = newIndex;
	if (language == 'e')
	{		
		SetMaterial();
	}
	else
	{
		SetMaterial('j');
	}
}

void ASignLetter::SetMaterial(char language)
{
	if (language == 'e')
	{
		if (MaterialIndex == 1)
		{
			Letter->SetMaterial(0, Material01);
		}

		else if (MaterialIndex == 2)
		{
			Letter->SetMaterial(0, Material02);
		}

		else if (MaterialIndex == 3)
		{
			Letter->SetMaterial(0, Material03);
		}
	}
	else 
	{
		if (MaterialIndex == 1)
		{
			Letter->SetMaterial(0, Material01_Jp);
		}

		else if (MaterialIndex == 2)
		{
			Letter->SetMaterial(0, Material02_Jp);
		}

		else if (MaterialIndex == 3)
		{
			Letter->SetMaterial(0, Material03_Jp);
		}
	}
}

uint8 ASignLetter::GetMaterialIndex()
{
	return MaterialIndex;
}

