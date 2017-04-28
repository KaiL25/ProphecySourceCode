// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Painting.h"


// Sets default values
APainting::APainting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Painting = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Painting"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_Painting(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (StaticMeshOb_Painting.Object)
		Painting->SetStaticMesh(StaticMeshOb_Painting.Object);
	Painting->SetWorldScale3D(FVector(1, 0.05, 1));
}

// Called when the game starts or when spawned
void APainting::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APainting::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APainting::SetPaintingMaterial(uint8 NewMaterialIndex)
{
	if (NewMaterialIndex == 0 || NewMaterialIndex == 2 || NewMaterialIndex == 4)
	{
		Painting->SetMaterial(0, Material01);
	}

	else if (NewMaterialIndex == 1 || NewMaterialIndex == 3 || NewMaterialIndex == 5)
	{
		Painting->SetMaterial(0, Material02);
	}
}