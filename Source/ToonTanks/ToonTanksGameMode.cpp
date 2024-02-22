// Fill out your copyright notice in the Description page of Project Settings.



#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h" 

AToonTanksGameMode::AToonTanksGameMode()
{
    // Ses bileşeninizi oluşturun
    MyAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MyAudioComponent"));
    MyAudioComponent->bAutoActivate = false; 
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();

    if(LofiPlayerCue && MyAudioComponent)
    {
        MyAudioComponent->SetSound(LofiPlayerCue);
        MyAudioComponent->Play();
    }
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if(Tank && DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }

    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;

        if(TargetTowers == 0)
        {
            GameOver(true);
        }

    }
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController =  Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);

        FTimerHandle StartingTimeHandle;
        GetWorldTimerManager().SetTimer(StartingTimeHandle, this, &AToonTanksGameMode::StartingTimer, 3.f, false);
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}
