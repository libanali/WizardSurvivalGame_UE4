// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SkeletalMeshComponent.h"
#include "WizardMan_GameMode.h"
#include "Particles/ParticleSystem.h"
#include "WizardCharacter_Class.generated.h"


class UCPP_GameplayWidget;

UCLASS()
class SURVIVEPROJECT_API AWizardCharacter_Class : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWizardCharacter_Class();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* Camera;


	void MoveForward(float Axis);
	void MoveRight(float Axis);


	
	void Death();

	void DrainMP();
	void StartMPDrain();

	void VictoryMenuActivation();


	


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Seconds;


	void GameTimer();
	void StartGameTimer();



	bool bDead;
	bool bCanDrainMP = false;
	bool bCanSpawnPotions = true;
	bool bDoOnce;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power")
		float Power;


	UPROPERTY(EditAnywhere, Category = "Power")
		float Power_Threshold;


	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> PowerWidgetClass;
	UUserWidget* PowerWidget;
		

	
	UPROPERTY()
		class AWizardMan_GameMode* WizardGameMode;


		FTimerHandle Draining2;

		FTimerHandle theGameTimer2;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vibration")
			UForceFeedbackEffect* MPCollectVibration;


	UPROPERTY(EditAnywhere, Category = "Explosion");
		UParticleSystem* DeathExplosion;
		
		 

		UPROPERTY(EditAnywhere, Category = "UI")
			TSubclassOf<UUserWidget> VictoryWidgetClass;
		UUserWidget* VictoryWidget;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
