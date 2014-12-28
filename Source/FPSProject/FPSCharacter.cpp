// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSCharacter.h"
#include "FPSProjectile.h"

AFPSCharacter::AFPSCharacter(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();

	//position the camera above the eyes
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//Create a mesh component that will be used when being viewed from a 1st person veiw (when controlling this pawn)
	FirstPersonMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	//everyone but the owner can see the third person mesh
	GetMesh()->SetOwnerNoSee(true);
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
	//setupr control for firing
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);
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
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		//add movement in the direction the camera is facing
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::OnFire()
{
	//try to fire a projectile
	if (ProjectileClass != NULL)
	{
		//Get the current camera transform
		FVector CameraLocation;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLocation, CameraRot);
		//MuzzleOffset is in camera space, so transform it to world space before offsetting the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLocation + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f; //skew the aim slightly upwards
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			//spawn the projectile at the muzzle.
			AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}