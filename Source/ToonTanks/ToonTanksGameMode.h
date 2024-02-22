// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UFUNCTION(BlueprintImplementableEvent)
	void StartingTimer();

	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetElapsedTime() const
{
    return ElapsedTime;
}

public:
	
	AToonTanksGameMode();
	void ActorDied(AActor* DeadActor);

private:

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;
	float ElapsedTime;

	void HandleGameStart();

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	UPROPERTY(EditAnywhere, category = "Music")
	class USoundCue* LofiPlayerCue;

	class UAudioComponent* MyAudioComponent;
};
