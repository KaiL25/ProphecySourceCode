// Fill out your copyright notice in the Description page of Project Settings.

#include "Prophecy.h"
#include "Statue.h"


AStatue::AStatue()
{
	statue = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Statue"));
	statue->SetupAttachment(axis);
}

