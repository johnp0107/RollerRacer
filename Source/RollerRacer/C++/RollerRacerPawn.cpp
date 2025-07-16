// Fill out your copyright notice in the Description page of Project Settings.

#include "RollerRacerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

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
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SocketOffset.Z = 250.0f;
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

void ARollerRacerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemplateRollerRacerPawn, Warning, TEXT("PlayerController not found in SetupPlayerInputComponent"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemplateRollerRacerPawn, Error, TEXT("EnhancedInputComponent not found! Ensure Enhanced Input system is used."));
		return;
	}

	// Bind all input actions only once here.
	EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::Steering);
	EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::Throttle);
	EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ARollerRacerPawn::ReleaseThrottle);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &ARollerRacerPawn::Pause);
	EnhancedInputComponent->BindAction(UpDownSelectorAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::UpDownSelector);
	EnhancedInputComponent->BindAction(ConfirmSelectionAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::ConfirmSelection);
	EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::Back);
}

void ARollerRacerPawn::BeginPlay()
{
	Super::BeginPlay();
	RacingComponent->IsMovingForward = true;
	RacingComponent->CurrentLapNumber = 0;
	RacingComponent->ForwardCheckPointCounter = 4;
	RacingComponent->BackwardCheckPointCounter = 3;
	RacingComponent->MoveForce = 0;
	MaxSpeed = 2000;

	if (Camera && Mesh)
	{
		const float TargetPitch = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), Mesh->GetComponentLocation()).Pitch;
		const FRotator CameraRot = Camera->GetComponentRotation();
		Camera->SetWorldRotation(FRotator(TargetPitch, CameraRot.Yaw, CameraRot.Roll));
	}

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASplineTrack::StaticClass());
	if (FoundActor)
	{
		SplineActor = Cast<ASplineTrack>(FoundActor);
		if (SplineActor)
		{
			SplineComponent = SplineActor->SplineComponent;
		}
	}

	GameInstance = Cast<URollerRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		if (Mesh)
		{
			Mesh->SetStaticMesh(GameInstance->StaticMesh);
			Mesh->SetMaterial(0, GameInstance->Material);
		}

		ActorTextures.SetNum(GameInstance->AIRacerNumber + 1);
	}

	RacerGameMode = Cast<ARollerRacerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (RacePositionWidgetInstance == nullptr && RaceTrackingWidgetClass)
	{
		RacePositionWidgetInstance = CreateWidget<URaceTrackingWidget>(GetWorld(), RaceTrackingWidgetClass);
		if (RacePositionWidgetInstance)
		{
			RacePositionWidgetInstance->AddToViewport();
		}
	}

	if (RaceOverWidgetInstance == nullptr && RaceOverWidgetClass)
	{
		RaceOverWidgetInstance = CreateWidget<URaceOverWidget>(GetWorld(), RaceOverWidgetClass);
		if (RaceOverWidgetInstance)
		{
			RaceOverWidgetInstance->AddToViewport();
		}
	}

	LevelAudio = UGameplayStatics::SpawnSound2D(this, MySoundWave, 1.f, 1.f, 0.f, nullptr, true);
	WrongWayAudio = UGameplayStatics::SpawnSound2D(this, WrongWayWave, 0.f, 1.f, 0.f, nullptr, true);

	RacingComponent->PassInfoFromParent(Mesh, SplineComponent, LevelSceneComponent, this, SpringArm);

	if (Mesh && SplineComponent)
	{
		FVector StartLocation = Mesh->GetComponentLocation();
		const float Distance = RacingComponent->GetDistance(StartLocation);

		// Adjust Z-location based on mesh shape bounds efficiently.
		const FString MeshFullName = Mesh->GetStaticMesh()->GetFullName();

		if (MeshFullName.Contains("Sphere"))
		{
			const FTransform WorldTransform = Mesh->GetComponentTransform();
			const FBoxSphereBounds SphereBounds = Mesh->CalcBounds(WorldTransform);
			const float RadiusValue = SphereBounds.SphereRadius;

			FVector ResetPosition = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			FVector UpVector = SplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			FVector Direction = UpVector * RadiusValue;

			FVector AdjustedLocation = ResetPosition + Direction;
			StartLocation.Z = AdjustedLocation.Z + 20.f;

			Mesh->SetWorldLocation(StartLocation);
		}
		else if (MeshFullName.Contains("Cylinder"))
		{
			const FBoxSphereBounds MeshBounds = Mesh->GetStaticMesh()->GetBounds();
			const float RadiusValue = FMath::Max(MeshBounds.BoxExtent.X, MeshBounds.BoxExtent.Y);

			FVector ResetPosition = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			FVector UpVector = SplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			FVector Direction = UpVector * RadiusValue + FVector(0.f, 0.f, 5.f);

			FVector AdjustedLocation = ResetPosition + Direction;
			StartLocation.Z = AdjustedLocation.Z;

			Mesh->SetWorldLocation(StartLocation);
		}
	}

	//NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Materials/NS_Projectile_05.NS_Projectile_05"));
	Mesh->SetMobility(EComponentMobility::Static);
}

void ARollerRacerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FString& StartTimerText = RacerGameMode->StartTimerText;
	RacePositionWidgetInstance->SetRaceCountdownText(StartTimerText);

	if (StartTimerText.Equals(TEXT("GO!")))
	{
		if (!GetWorldTimerManager().IsTimerActive(DisplayGoTimerHandle))
		{
			GetWorldTimerManager().SetTimer(DisplayGoTimerHandle, this, &ARollerRacerPawn::DisplayGoTimer, 2.0f, false);
		}
	}
	const bool bIsMeshMobility = Mesh->Mobility != EComponentMobility::Static;

	if (bIsMeshMobility)
	{
		const FVector MeshLocation = Mesh->GetComponentLocation();

		// Cache distance only once per Tick
		float Distance = RacingComponent->GetDistance(MeshLocation);

		RacingComponent->CheckActorAboveFloor();

		RacingComponent->SetForwardAndDownVelocity(Distance, SplineComponent, SpringArm, Mesh);
		RacingComponent->TrackPlayerProgress(Distance);

		UpdateRaceWidget(Distance, DeltaTime);

		TotalDistanceTravelled = RacingComponent->TotalDistanceTravelled;
	}

	if (RacingComponent->IsMovingForward)
	{
		HideBackwardsDisplay = true;
		if (LevelAudio->VolumeMultiplier != 1.0f)
		{
			LevelAudio->SetVolumeMultiplier(1.0f);
		}

		if (WrongWayAudio->VolumeMultiplier != 0.0f)
		{
			WrongWayAudio->SetVolumeMultiplier(0.0f);
		}
		GetWorld()->GetTimerManager().ClearTimer(ThreeSecondTimerHandle);
	}
	else
	{
		if (!GetWorldTimerManager().IsTimerActive(ThreeSecondTimerHandle))
		{
			GetWorldTimerManager().SetTimer(ThreeSecondTimerHandle, this, &ARollerRacerPawn::ThreeSecondCountdownTimer, 2.0f, false);
		}
	}

	const bool bContinueVisible = RacePositionWidgetInstance->ContinueTextBlock->GetVisibility() == ESlateVisibility::Visible;
	const bool bMainMenuVisible = RacePositionWidgetInstance->MainMenuTextBlock->GetVisibility() == ESlateVisibility::Visible;

	if (bContinueVisible)
	{
		RacePositionWidgetInstance->HighlightPauseMenuText(TextCount);
	}
	if (bMainMenuVisible)
	{
		RacePositionWidgetInstance->HighlightFinishedRaceMenuText(TextCount);
	}
}

void ARollerRacerPawn::Throttle(const FInputActionValue& Value)
{
	if (!Mesh)
		return;

	double FloatValue = Value.Get<float>();
	float AccelerationValue = 10;

	if (Mesh->Mobility != EComponentMobility::Static && RacingComponent)
	{
		if (RacingComponent->MoveForce < MaxSpeed && RacingComponent->MoveForce > -500)
		{
			RacingComponent->MoveForce += (FloatValue * AccelerationValue);
			RacingComponent->SlowDown = false;
		}
		else if (RacingComponent->MoveForce > MaxSpeed + 10)
		{
			RacingComponent->SlowDown = true;
		}
	}
}

void ARollerRacerPawn::ReleaseThrottle(const FInputActionValue& Value)
{
	if (RacingComponent)
	{
		RacingComponent->SlowDown = true;
	}
}

void ARollerRacerPawn::Steering(const FInputActionValue& Value)
{
	if (!Mesh)
		return;

	if (Mesh->Mobility != EComponentMobility::Static)
	{
		double FloatValue = Value.Get<float>();
		SpringArm->AddLocalRotation(FRotator(0.f, FloatValue, 0.f));
	}
}


void ARollerRacerPawn::Pause(const FInputActionValue& Value)
{
	if (!RacingComponent || !GameInstance || !RacerGameMode || !RacePositionWidgetInstance)
		return;

	if (RacingComponent->CurrentLapNumber <= GameInstance->NumberOfLaps)
	{
		if (Mesh && Mesh->Mobility != EComponentMobility::Static)
		{
			RacerGameMode->PauseRace();
			TextCount = 0;

			RacePositionWidgetInstance->ContinueTextBlock->SetVisibility(ESlateVisibility::Visible);
			RacePositionWidgetInstance->OptionsTextBlock->SetVisibility(ESlateVisibility::Visible);
			RacePositionWidgetInstance->QuitTextBlock->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			RacePositionWidgetInstance->ContinueTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacePositionWidgetInstance->OptionsTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacePositionWidgetInstance->QuitTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacerGameMode->UnPauseRace();
		}
	}
	else
	{
		if (Mesh && Mesh->Mobility != EComponentMobility::Static)
		{
			TextCount = 0;
			RaceOverWidgetInstance->HideRaceOverCanvas();

			RacePositionWidgetInstance->MainMenuTextBlock->SetVisibility(ESlateVisibility::Visible);
			RacePositionWidgetInstance->QuitTextBlock->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ARollerRacerPawn::UpDownSelector(const FInputActionValue& Value)
{
	if (!RacePositionWidgetInstance)
		return;

	const double FloatValue = Value.Get<float>();
	if (RacePositionWidgetInstance->ContinueTextBlock && RacePositionWidgetInstance->ContinueTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		if (FloatValue > 0 && TextCount > 0)
		{
			--TextCount;
		}
		else if (FloatValue < 0 && TextCount < RacePositionWidgetInstance->PauseMenuTextList.Num() - 1)
		{
			++TextCount;
		}
	}
	else if (RacePositionWidgetInstance->MainMenuTextBlock && RacePositionWidgetInstance->MainMenuTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		if (FloatValue > 0 && TextCount > 0)
		{
			--TextCount;
		}
		else if (FloatValue < 0 && TextCount < RacePositionWidgetInstance->FinishedRaceTextList.Num() - 1)
		{
			++TextCount;
		}
	}
}

void ARollerRacerPawn::ConfirmSelection(const FInputActionValue& Value)
{
	if (!RacePositionWidgetInstance)
		return;

	if (RacePositionWidgetInstance->ContinueTextBlock && RacePositionWidgetInstance->ContinueTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		if (RacePositionWidgetInstance->ContinueTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			RacePositionWidgetInstance->ContinueTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacePositionWidgetInstance->OptionsTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacePositionWidgetInstance->QuitTextBlock->SetVisibility(ESlateVisibility::Hidden);

			if (RacerGameMode)
			{
				RacerGameMode->UnPauseRace();
			}
		}
		else if (RacePositionWidgetInstance->OptionsTextBlock && RacePositionWidgetInstance->OptionsTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			RacePositionWidgetInstance->ContinueTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacePositionWidgetInstance->OptionsTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacePositionWidgetInstance->QuitTextBlock->SetVisibility(ESlateVisibility::Hidden);
			RacePositionWidgetInstance->ComingSoonTextBlock->SetVisibility(ESlateVisibility::Visible);
			RacePositionWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Visible);
		}
		else if (RacePositionWidgetInstance->QuitTextBlock && RacePositionWidgetInstance->QuitTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
		}
	}
	else if (RacePositionWidgetInstance->MainMenuTextBlock && RacePositionWidgetInstance->MainMenuTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		if (RacePositionWidgetInstance->MainMenuTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			UWorld* World = GetWorld();
			if (World)
			{
				UGameplayStatics::OpenLevel(World, FName("MainMenu"));
			}
		}
		else if (RacePositionWidgetInstance->QuitTextBlock && RacePositionWidgetInstance->QuitTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
		}
	}
}

void ARollerRacerPawn::Back(const FInputActionValue& Value)
{
	if (!RacePositionWidgetInstance)
		return;

	if (RacePositionWidgetInstance->ContinueTextBlock && RacePositionWidgetInstance->ContinueTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		RacePositionWidgetInstance->ContinueTextBlock->SetVisibility(ESlateVisibility::Visible);
		RacePositionWidgetInstance->OptionsTextBlock->SetVisibility(ESlateVisibility::Visible);
		RacePositionWidgetInstance->QuitTextBlock->SetVisibility(ESlateVisibility::Visible);
		RacePositionWidgetInstance->ComingSoonTextBlock->SetVisibility(ESlateVisibility::Hidden);
		RacePositionWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Hidden);
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
	WrongWayAudio->SetVolumeMultiplier(1.0f);
	GetWorldTimerManager().ClearTimer(ThreeSecondTimerHandle);
}

void ARollerRacerPawn::OutOfSpeedZoneTimer()
{
	//NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, Mesh->GetComponentLocation(), Mesh->GetRelativeRotation());
	if (!GetWorldTimerManager().IsTimerActive(OutOfSpeedZoneTimerHandle))
	{
		GetWorldTimerManager().SetTimer(
			OutOfSpeedZoneTimerHandle,
			this,
			&ARollerRacerPawn::ResetMaxSpeed,
			2.0f,
			false);
	}
	
}

void ARollerRacerPawn::ResetMaxSpeed()
{
	MaxSpeed = 2000;
	//NiagaraComponent->Deactivate();
}

void ARollerRacerPawn::UpdateRaceWidget(float Distance, float DeltaTime)
{
	if (!RacerGameMode || !RacePositionWidgetInstance || !GameInstance)
		return;

	Position = RacerGameMode->GetActorPosition(this);
	RacePositionWidgetInstance->SetPositionText(FString::FromInt(Position));
	RacePositionWidgetInstance->DisplayWrongWayText(HideBackwardsDisplay);

	const int32 MoveForce = RacingComponent ? RacingComponent->MoveForce : 0;

	if (MoveForce >= 0)
	{
		RacePositionWidgetInstance->SetSpeedText(FString::FromInt(MoveForce / 10));
	}
	else
	{
		RacePositionWidgetInstance->SetSpeedText(FString::Printf(TEXT("R%d"), (-MoveForce) / 10));
	}

	NumLapsCompleted = (RacingComponent && RacingComponent->CurrentLapNumber > 0) ? RacingComponent->CurrentLapNumber : 1;
	int32 TotalLaps = GameInstance->NumberOfLaps;

	if (TotalLaps > 0)
	{
		RacePositionWidgetInstance->SetLapText(FString::FromInt(NumLapsCompleted), FString::FromInt(TotalLaps));
	}

	if (NumLapsCompleted > TotalLaps)
	{
		auto& Widget = RacePositionWidgetInstance;
		Widget->SpeedTextBlock->SetVisibility(ESlateVisibility::Hidden);
		Widget->PositionTextBlock->SetVisibility(ESlateVisibility::Hidden);
		Widget->LapTextBlock->SetVisibility(ESlateVisibility::Hidden);
		Widget->FirstPlaceImage->SetVisibility(ESlateVisibility::Hidden);
		Widget->FirstPlaceText->SetVisibility(ESlateVisibility::Hidden);
		Widget->SecondPlaceImage->SetVisibility(ESlateVisibility::Hidden);
		Widget->SecondPlaceText->SetVisibility(ESlateVisibility::Hidden);
		Widget->ThirdPlaceImage->SetVisibility(ESlateVisibility::Hidden);
		Widget->ThirdPlaceText->SetVisibility(ESlateVisibility::Hidden);
		Widget->ForthPlaceImage->SetVisibility(ESlateVisibility::Hidden);
		Widget->ForthPlaceText->SetVisibility(ESlateVisibility::Hidden);

		MaxSpeed = 1500;
		AutoDriving(DeltaTime);

		const int32 FinishedCount = RacerGameMode->RacerFinishedRaceList.Num();
		FinishedRacerTextures.SetNum(FinishedCount);
		TMap<FName, UTexture2D*> NameToTextureMap;
		for (UTexture2D* Texture : RacerGameMode->ActorTextures)
		{
			if (Texture)
			{
				NameToTextureMap.Add(Texture->GetFName(), Texture);
			}
		}

		for (int32 FinishedRacerNum = 0; FinishedRacerNum < FinishedCount; ++FinishedRacerNum)
		{
			const FName FinishedName = RacerGameMode->RacerFinishedRaceList[FinishedRacerNum]->GetFName();
			if (UTexture2D** FoundTexture = NameToTextureMap.Find(FinishedName))
			{
				FinishedRacerTextures[FinishedRacerNum] = *FoundTexture;
			}
			else
			{
				FinishedRacerTextures[FinishedRacerNum] = nullptr;
			}
		}

		RaceOverWidgetInstance->SetFinishPositionImage(FinishedRacerTextures);
	}
	else
	{
		const int32 NumRacers = RacerGameMode->FoundActors.Num();
		ActorTextures.SetNum(NumRacers);

		TMap<FName, UTexture2D*> NameToTextureMap;
		for (UTexture2D* Texture : RacerGameMode->ActorTextures)
		{
			if (Texture)
			{
				NameToTextureMap.Add(Texture->GetFName(), Texture);
			}
		}

		for (int32 ActorNum = 0; ActorNum < NumRacers; ++ActorNum)
		{
			const FName FoundActorName = RacerGameMode->FoundActors[ActorNum]->GetFName();
			if (UTexture2D** FoundTexture = NameToTextureMap.Find(FoundActorName))
			{
				ActorTextures[ActorNum] = *FoundTexture;
			}
			else
			{
				ActorTextures[ActorNum] = nullptr;
			}
		}

		RacePositionWidgetInstance->SetPositionImages(ActorTextures);

		if (!RacerGameMode->ActorTextures.Contains(PlayerTexture))
		{
			PlayerTexture = CaptureTexture->ConvertStaticMeshToTexture2D(this, Mesh, LevelSceneComponent);
			if (PlayerTexture)
			{
				PlayerTexture->Rename(*GetName(), PlayerTexture->GetOuter());
				RacerGameMode->ActorTextures.Add(PlayerTexture);
			}
		}
	}
}

void ARollerRacerPawn::AutoDriving(float DeltaTime)
{
	if (!SplineComponent || !Mesh || !LevelSceneComponent || !RacingComponent)
		return;

	const float InputKey = SplineComponent->FindInputKeyClosestToWorldLocation(Mesh->GetComponentLocation());
	const float Distance = SplineComponent->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	const FVector NewTarget = SplineComponent->GetLocationAtDistanceAlongSpline(Distance + 500.f, ESplineCoordinateSpace::World);
	SplineLocation = FMath::VInterpTo(SplineLocation, NewTarget, DeltaTime, 10.f);

	const FTransform LevelForwardTransform = LevelSceneComponent->GetComponentTransform();
	const FVector LevelInverse = LevelForwardTransform.InverseTransformPosition(SplineLocation);
	const float AngleToSplinePoint = UKismetMathLibrary::MakeRotFromX(LevelInverse).Yaw;

	const int32 MoveForce = RacingComponent->MoveForce;

	if (AngleToSplinePoint < -5)
	{
		Steering(-1);
		if (AngleToSplinePoint >= -10)
		{
			Throttle(1);
		}
		else if (AngleToSplinePoint >= -20)
		{
			Throttle(MoveForce > 1000 ? 0 : 1);
		}
		else if (AngleToSplinePoint >= -30)
		{
			Throttle(MoveForce > 750 ? -1 : 1);
		}
		else
		{
			Throttle(MoveForce > 500 ? -1 : 1);
		}
	}
	else if (AngleToSplinePoint > 5)
	{
		Steering(1);
		if (AngleToSplinePoint <= 10)
		{
			Throttle(1);
		}
		else if (AngleToSplinePoint <= 20)
		{
			Throttle(MoveForce > 1000 ? 0 : 1);
		}
		else if (AngleToSplinePoint <= 30)
		{
			Throttle(MoveForce > 750 ? -1 : 1);
		}
		else
		{
			Throttle(MoveForce > 500 ? -1 : 1);
		}
	}
	else
	{
		Steering(0);
		Throttle(1);
	}
}

//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, AdjustedLocation.ToString());

#undef LOCTEXT_NAMESPACE