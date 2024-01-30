// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
    SpringArmComponent ->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent ->SetupAttachment(SpringArmComponent);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value*Speed;
	AddActorLocalOffset(DeltaLocation);
	UE_LOG(LogTemp, Display, TEXT("W is working value is = %f"),DeltaLocation.X);
}




