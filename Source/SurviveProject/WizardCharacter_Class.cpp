// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardCharacter_Class.h"
#include "Kismet/GameplayStatics.h"
#include "WizardMan_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
AWizardCharacter_Class::AWizardCharacter_Class()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->AirControl = 0.1f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	bDead = false;

	Power = 100.0f;

	Minutes = 0;
	Seconds = 20;

}




void AWizardCharacter_Class::MoveForward(float Axis)
{

	if (!bDead)
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);

	}
}





void AWizardCharacter_Class::MoveRight(float Axis)
{

	if (!bDead)
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);

	}



}





void AWizardCharacter_Class::Death()
{


	if (Power <= 0.0f)
	{
		Power = 0.0f;

		bDead = true;

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("DEAD"));
		
		GetWorld()->GetTimerManager().ClearTimer(theGameTimer2);

		WizardGameMode->ClearTheTimer();

	
			FVector ExplosionLocation = GetActorLocation();
			FRotator ExplosionRotation = GetActorRotation();

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathExplosion, ExplosionLocation, ExplosionRotation, true);

			Destroy(true);
	}

}








void AWizardCharacter_Class::StartMPDrain()

{

	bCanDrainMP = true;


}




void AWizardCharacter_Class::DrainMP()
{

	Power -= 0.02f;

}






void AWizardCharacter_Class::GameTimer()
{




	if (Seconds != 0)

	{

		Seconds -= 1;

	}

	else

	{
		if (Minutes == 0 && Seconds == 0)
		{

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("time is up"));


			WizardGameMode->ClearTheTimer();

		
		}

		else

		{
			Minutes -= 1;
			Seconds = 59;
		}


		if (Minutes == 0 && Seconds == 0 && Power > 0)

		{

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("you did it!"));

			// make an FVector and make it equivalent to the victory spawn location

			FVector NewLocation = FVector(-249.0f, 31.0f, 198.0f);
			FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);

			SetActorLocationAndRotation(NewLocation, NewRotation);

			
			GetWorld()->GetTimerManager().ClearTimer(theGameTimer2);

			VictoryMenuActivation();


		}

	}

}










void AWizardCharacter_Class::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Potion"))

	{

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Collided!"));

		Power += 10.0f;

		OtherActor->Destroy();

		APlayerController* PSController = GetWorld()->GetFirstPlayerController();
		
		PSController->ClientPlayForceFeedback(MPCollectVibration);
		


		if (Power > 100.0f)
		{
			Power = 100.0f;

		}

	}

}








// Called when the game starts or when spawned
void AWizardCharacter_Class::BeginPlay()
{
	Super::BeginPlay();


	WizardGameMode = Cast<AWizardMan_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));


	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AWizardCharacter_Class::OnBeginOverlap);

	
	//FTimerHandle TheGameTimer;

	GetWorld()->GetTimerManager().SetTimer(theGameTimer2, this, &AWizardCharacter_Class::GameTimer, 1.0f, true, 4.0f);



	GetWorld()->GetTimerManager().SetTimer(Draining2, this, &AWizardCharacter_Class::StartMPDrain, 4.0f, false); 


	if (PowerWidgetClass != nullptr)
	{

		PowerWidget = CreateWidget(GetWorld(), PowerWidgetClass);

		PowerWidget->AddToViewport();

	}


}








// Called every frame
void AWizardCharacter_Class::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	


	Power = FMath::Clamp(Power, 0.0f, 100.0f);




	Death();





	bool bGameOver = Minutes == 0 && Seconds == 0;

	if (bGameOver == false && bCanDrainMP == true)
	{
		DrainMP();
	}


	


}









// Called to bind functionality to input
void AWizardCharacter_Class::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAxis("MoveForward", this, &AWizardCharacter_Class::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWizardCharacter_Class::MoveRight);


}


void AWizardCharacter_Class::VictoryMenuActivation()
{


		VictoryWidget = CreateWidget(GetWorld(), VictoryWidgetClass);

		VictoryWidget->AddToViewport();

	


}



