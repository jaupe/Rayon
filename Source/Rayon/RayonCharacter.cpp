// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RayonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"

ARayonCharacter::ARayonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	CameraDirection = EDirection::North;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARayonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("RotateLeft", IE_Pressed, this, &ARayonCharacter::RotateLeft);
	PlayerInputComponent->BindAction("RotateRight", IE_Pressed, this, &ARayonCharacter::RotateRight);
	// set up gameplay key axis
	PlayerInputComponent->BindAxis("MoveRight", this, &ARayonCharacter::MoveRight);
}

void ARayonCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(GetPlayerDirection(), Value);
}

void ARayonCharacter::RotateLeft()
{
	// rotate camera left
	CameraBoom->AddLocalRotation(FRotator(0, 90, 0));
	// update state of camera direction for correct player direction
	switch (CameraDirection) {
	case EDirection::North:
		CameraDirection = EDirection::West;
		break;
	case EDirection::West:
		CameraDirection = EDirection::South;
		break;
	case EDirection::South:
		CameraDirection = EDirection::East;
		break;
	case EDirection::East:
		CameraDirection = EDirection::North;
		break;
	}
}

void ARayonCharacter::RotateRight()
{
	// rotate camera right
	CameraBoom->AddLocalRotation(FRotator(0, -90, 0));
	// update state of camera direction for correct player direction
	switch (CameraDirection) {
	case EDirection::North:
		CameraDirection = EDirection::East;
		break;
	case EDirection::West:
		CameraDirection = EDirection::North;
		break;
	case EDirection::South:
		CameraDirection = EDirection::West;
		break;
	case EDirection::East:
		CameraDirection = EDirection::South;
		break;
	}
}

/* returns a normalized direction vector so player can walk left or right correctly when rotating camera*/
FVector ARayonCharacter::GetPlayerDirection()
{
	switch (CameraDirection) {
	case EDirection::North:
		return FVector(0, -1, 0);
	case EDirection::West:
		return FVector(1, 0, 0);
	case EDirection::South:
		return FVector(0, 1, 0);
	case EDirection::East:
		return FVector(-1, 0, 0);
	default:
		return FVector(-1, 0, 0);
	}
}