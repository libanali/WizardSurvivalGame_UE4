// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WizardMan_GameMode.generated.h"

/**
 * 
 */


UCLASS()
class SURVIVEPROJECT_API AWizardMan_GameMode : public AGameMode
{
	GENERATED_BODY()

		AWizardMan_GameMode();



	virtual void BeginPlay() override;


	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MP_Potion;

	float Spawn_Z = 500.0f;


	UPROPERTY(EditAnywhere)
		float Spawn_X_Min;


	UPROPERTY(EditAnywhere)
		float Spawn_X_Max;


	UPROPERTY(EditAnywhere)
		float Spawn_Y_Min;


	UPROPERTY(EditAnywhere)
		float Spawn_Y_Max;



	UFUNCTION()
	void SpawnMP_Potion();



	void SpawnMP_Potion_Timer();



	UPROPERTY()
		class AWizardCharacter_Class* WizardCharacter;




public:

	FTimerHandle MP_Potion_Timer;


	void ClearTheTimer();




};
