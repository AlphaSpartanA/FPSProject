// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSGameMode.h"
#include "Engine.h" //for version 4.4+


AFPSGameMode::AFPSGameMode(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	//set player pawn class to our blueprinted character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/BP_FPSCharacter.BP_FPSCharacter'"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Failed to load chacrater blueprint."));
		}
	}
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