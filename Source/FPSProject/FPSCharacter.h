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

public: 
	virtual void BeginPlay() override;
	//sets jump flag when key is pressed
	UFUNCTION()
	void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
	void OnStopJump();
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FirstPersonCameraComponent;
	/**Pawn Mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FirstPersonMesh;
	/** Gun muzzle's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	/** projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;
		
protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//handles mocing forward and backward
	UFUNCTION()
	void MoveForward(float Val);
	//handles moving left or right (strafing)
	UFUNCTION()
	void MoveRight(float Val);
	//handles firing
	UFUNCTION()
	void OnFire();
};
