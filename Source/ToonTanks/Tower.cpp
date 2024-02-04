// Fill out your copyright notice in the Description page of Project Settings.
#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


ATower::ATower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance<=FireRange)
        {
            RotateTurret(Tank->GetActorLocation(),TowerTurnSpeed);
        }
    }
}


