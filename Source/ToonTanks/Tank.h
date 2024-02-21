// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{	
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 833;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnRate = 60;
	UPROPERTY(EditAnywhere)
	float TankTurretTurnRate = 5.f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const {return TankPlayerController;}

	bool balive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

	void Move(float Value);

	void Turn(float Value);

	APlayerController* TankPlayerController;
};
