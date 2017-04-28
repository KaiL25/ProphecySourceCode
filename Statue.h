// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "Statue.generated.h"

/**
 * 
 */
UCLASS()
class PROPHECY_API AStatue : public APickUp
{
	GENERATED_BODY()

public:

	AStatue();
	UPROPERTY(EditAnywhere, Category = "Statue")
	USkeletalMeshComponent* statue;
	
};
