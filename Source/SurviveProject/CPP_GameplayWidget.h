// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVEPROJECT_API UCPP_GameplayWidget : public UUserWidget
{
	GENERATED_BODY()


		UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* EndOFGameMPBar_Anim;


	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* EndOFGameTimer_Anim;



	void PlayEndingAnimation();
	void DeathMenuActivation();



};
