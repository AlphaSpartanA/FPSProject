// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{

}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are suing FPSCharacter"));
	}
}

void AFPSCharacter::OnStartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::OnStopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	//setup gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);//walking forwards of backwards
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);//walking left or right
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);//looking left or right
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);//looking up or down
	//setup controls for jumping
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::OnStopJump);
}

void AFPSCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		//limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		//add movement in the direction the camera is facing
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0))
	{
		//find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		//add movement in the direction the camera is facing
		AddMovementInput(Direction, Value);
	}
}