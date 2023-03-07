// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardMan_GameMode.h"
#include "GameFramework/Actor.h"
#include "WizardCharacter_Class.h"
#include "TimerManager.h"



AWizardMan_GameMode::AWizardMan_GameMode()

{

	PrimaryActorTick.bCanEverTick = true;


}


void AWizardMan_GameMode::BeginPlay()

{

	Super::BeginPlay();


	
	FTimerHandle MP_Potion_BeginningTimer;


	SpawnMP_Potion_Timer();

//	GetWorld()->GetTimerManager().SetTimer(MP_Potion_BeginningTimer, this, &AWizardMan_GameMode::SpawnMP_Potion_Timer, 4.9f);

}

void AWizardMan_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




}

void AWizardMan_GameMode::SpawnMP_Potion()
{

	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);


	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	GetWorld()->SpawnActor(MP_Potion, &SpawnPosition, &SpawnRotation);



}

void AWizardMan_GameMode::SpawnMP_Potion_Timer()
{

	//FTimerHandle MP_Potion_Timer;


	GetWorld()->GetTimerManager().SetTimer(MP_Potion_Timer, this, &AWizardMan_GameMode::SpawnMP_Potion, FMath::RandRange(1, 3), true, 4.9f);


}


void AWizardMan_GameMode::ClearTheTimer()

{

	GetWorld()->GetTimerManager().ClearTimer(MP_Potion_Timer);

}
