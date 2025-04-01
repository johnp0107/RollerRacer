// Fill out your copyright notice in the Description page of Project Settings.

#include "RollerRacerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "RollerRacerPawn"

DEFINE_LOG_CATEGORY(LogTemplateRollerRacerPawn);

ARollerRacerPawn::ARollerRacerPawn()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	SetRootComponent(Mesh);

	// Create the SpringArm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset.Z = 150;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 3;

	LevelSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Level"));
	LevelSceneComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Create the Camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	CaptureTexture = CreateDefaultSubobject<UCaptureTextureSnapshot>(TEXT("CaptureTexture"));
	MySoundWave = LoadObject<USoundWave>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Audio/RaceTrack1Audio.RaceTrack1Audio'"));
	WrongWayWave = LoadObject<USoundWave>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Audio/WrongWayWave.WrongWayWave'"));

	RacingComponent = CreateDefaultSubobject<URacingComponent>(TEXT("RacingComponent"));
}

// Called to bind functionality to input
void ARollerRacerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::Steering);

		// throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ARollerRacerPawn::ReleaseThrottle);
	}
	else
	{
		UE_LOG(LogTemplateRollerRacerPawn, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ARollerRacerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	RacingComponent->IsMovingForward = true;
	RacingComponent->NumLapsCompleted = -1;
	RacingComponent->ForwardCheckPointCounter = 4;
	RacingComponent->BackwardCheckPointCounter = 3;
	RacingComponent->MoveForce = 0;

	

	float TargetPitch = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), Mesh->GetComponentLocation()).Pitch;
	Camera->SetWorldRotation(FRotator(TargetPitch, Camera->GetComponentRotation().Yaw, Camera->GetComponentRotation().Roll));

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASplineTrack::StaticClass());
	if (FoundActor)
	{
		SplineActor = Cast<ASplineTrack>(FoundActor);
		SplineComponent = SplineActor->SplineComponent;
	}
	
	GameInstance = Cast<URollerRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Mesh->SetStaticMesh(GameInstance->StaticMesh);
	Mesh->SetMaterial(0, GameInstance->Material);
	Mesh->SetMobility(EComponentMobility::Static);
	ActorTextures.SetNum(GameInstance->AIRacerNumber + 1);

	RacerGameMode = Cast<ARollerRacerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (WidgetClass)
	{
		RacePositionWidgetInstance = CreateWidget<URaceTrackingWidget>(GetWorld(), WidgetClass);
		if (RacePositionWidgetInstance)
		{
			RacePositionWidgetInstance->AddToViewport();
		}
	}
	LevelAudio = UGameplayStatics::SpawnSound2D(this, MySoundWave, 1.0f, 1.0f, 0.0f, nullptr, true);
	WrongWayAudio = UGameplayStatics::SpawnSound2D(this, WrongWayWave, 0.0f, 1.0f, 0.0f, nullptr, true);
	RacingComponent->PassInfoFromParent(Mesh, SplineComponent, LevelSceneComponent, this, SpringArm);
}

void ARollerRacerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RacePositionWidgetInstance->SetRaceCountdownText(RacerGameMode->StartTimerText);
	if (RacerGameMode->StartTimerText == "GO!")
	{
		if (!GetWorldTimerManager().IsTimerActive(DisplayGoTimerHandle))
		{

			GetWorldTimerManager().SetTimer(
				DisplayGoTimerHandle,
				this,
				&ARollerRacerPawn::DisplayGoTimer,
				2.0f,
				false);
		}
	}
	if (Mesh->Mobility)
	{
		float Distance = RacingComponent->GetDistance(Mesh->GetComponentLocation());
		RacingComponent->CheckActorAboveFloor();
		RacingComponent->SetForwardAndDownVelocity(Distance, SplineComponent, SpringArm, Mesh);
		RacingComponent->TrackPlayerProgress(Distance);
		UpdateRaceWidget(Distance);
		TotalDistanceTravelled = RacingComponent->TotalDistanceTravelled;
	}

	if (RacingComponent->IsMovingForward)
	{
		HideBackwardsDisplay = true;
		LevelAudio->SetVolumeMultiplier(1.0f);
		WrongWayAudio->SetVolumeMultiplier(0.0f);
		GetWorld()->GetTimerManager().ClearTimer(ThreeSecondTimerHandle);
	}
	else
	{
		if (!GetWorldTimerManager().IsTimerActive(ThreeSecondTimerHandle))
		{
			GetWorldTimerManager().SetTimer(
				ThreeSecondTimerHandle,
				this,
				&ARollerRacerPawn::ThreeSecondCountdownTimer,
				2.0f,
				false);
		}
	}
}

void ARollerRacerPawn::Throttle(const FInputActionValue& Value)
{
	double FloatValue = Value.Get<float>();
	float AccelerationValue = 10;
	if (FloatValue > 0)
	{
		AccelerationValue = 10;
	}
	else
	{
		AccelerationValue = 15;
	}
	if (RacingComponent->MoveForce < 2000 && RacingComponent->MoveForce > -500)
	{
		RacingComponent->MoveForce += (FloatValue * AccelerationValue);
	}
	RacingComponent->SlowDown = false;
}

void ARollerRacerPawn::ReleaseThrottle(const FInputActionValue& Value)
{
	RacingComponent->SlowDown = true;
}

void ARollerRacerPawn::Steering(const FInputActionValue& Value)
{
	if (Mesh->Mobility)
	{
		double FloatValue = Value.Get<float>();
		SpringArm->AddLocalRotation(FRotator(0, FloatValue, 0));
	}
}

void ARollerRacerPawn::DisplayGoTimer()
{
	if (RacePositionWidgetInstance->CountdownTextBlock)
	{
		RacePositionWidgetInstance->CountdownTextBlock->SetVisibility(ESlateVisibility::Hidden);
		RacePositionWidgetInstance->CountdownTextBlock->RemoveFromParent();
		RacePositionWidgetInstance->CountdownTextBlock = nullptr;
	}
}

void ARollerRacerPawn::ThreeSecondCountdownTimer()
{
	HideBackwardsDisplay = false;
	LevelAudio->SetVolumeMultiplier(0.5f);
	WrongWayAudio->SetVolumeMultiplier(2.0f);
	GetWorldTimerManager().ClearTimer(ThreeSecondTimerHandle);
}

void ARollerRacerPawn::UpdateRaceWidget(float Distance)
{
	Position = RacerGameMode->GetActorPosition(this);
	RacePositionWidgetInstance->SetPositionText(FString::FromInt(Position));
	RacePositionWidgetInstance->DisplayWrongWayText(HideBackwardsDisplay);

	if (RacingComponent->MoveForce >= 0)
	{
		RacePositionWidgetInstance->SetSpeedText(FString::FromInt(RacingComponent->MoveForce / 10));
	}
	else
	{
		RacePositionWidgetInstance->SetSpeedText("R" + FString::FromInt((RacingComponent->MoveForce * -1) / 10));
	}

	if (RacingComponent->NumLapsCompleted > 0)
	{
		RacePositionWidgetInstance->SetLapText(FString::FromInt(RacingComponent->NumLapsCompleted));
	}
	else
	{
		RacePositionWidgetInstance->SetLapText(FString::FromInt(0));
	}

	for (int32 ActorNum = 0; ActorNum < RacerGameMode->FoundActors.Num(); ActorNum++)
	{
		for (int32 TextureNum = 0; TextureNum < RacerGameMode->ActorTextures.Num(); TextureNum++)
		{
			if (RacerGameMode->FoundActors[ActorNum]->GetName() == RacerGameMode->ActorTextures[TextureNum]->GetName())
			{
				ActorTextures[ActorNum] = RacerGameMode->ActorTextures[TextureNum];
			}
		}
	}
	RacePositionWidgetInstance->SetPositionImages(ActorTextures);

	if (!RacerGameMode->ActorTextures.Contains(PlayerTexture))
	{
		PlayerTexture = CaptureTexture->ConvertStaticMeshToTexture2D(this, Mesh, LevelSceneComponent);
		PlayerTexture->Rename(*this->GetName(), PlayerTexture->GetOuter());
		RacerGameMode->ActorTextures.Add(PlayerTexture);
	}
}


//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, AdjustedLocation.ToString());

#undef LOCTEXT_NAMESPACE