// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	AFPSCharacter(const FObjectInitializer& PCIP);

	virtual void BeginPlay() override;
		
protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//handles mocing forward and backward
	UFUNCTION()
	void MoveForward(float Val);
	//handles moving left or right (strafing)
	UFUNCTION()
	void MoveRight(float Val);
};
