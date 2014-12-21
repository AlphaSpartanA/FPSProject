// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSGameMode.h"
#include "Engine.h" //for version 4.4+
#include "FPSCharacter.h"


AFPSGameMode::AFPSGameMode(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	DefaultPawnClass = AFPSCharacter::StaticClass();
}

void AFPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartMatch();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}