// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSelectorPawn.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetMathLibrary.h"

#define LOCTEXT_NAMESPACE "SelectorPawn"

DEFINE_LOG_CATEGORY(LogTemplateSelectorPawn);

APlayerSelectorPawn::APlayerSelectorPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh1");
	Mesh1->SetSimulatePhysics(true);
	Mesh1->SetEnableGravity(false);
	SetRootComponent(Mesh1);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh1);
	SpringArm->TargetArmLength = 700;
	SpringArm->SocketOffset.Z = -100;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 3;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	static ConstructorHelpers::FObjectFinder<USoundWave> IntroWaveObject(TEXT("/Game/Audio/IntroAudio.IntroAudio"));
	if (IntroWaveObject.Succeeded())
	{
		IntroWave = IntroWaveObject.Object;
	}

	CaptureTexture = CreateDefaultSubobject<UCaptureTextureSnapshot>(TEXT("CaptureTexture"));
}

void APlayerSelectorPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentMeshCount = 0;
	MaterialCount = 0;
	MaxAIPlayerValue = 12;
	LapCount = 1;
	MaxLapCount = 5;
	AIPlayerCount = 0;
	TextCount = 0;
	CurrentTrackCount = 0;

	if (!WidgetClass)
	{
		UE_LOG(LogTemplateSelectorPawn, Warning, TEXT("WidgetClass not assigned in Blueprint"));
		return;
	}

	MainMenuWidgetInstance = CreateWidget<UGameStartWidget>(GetWorld(), WidgetClass);
	if (!MainMenuWidgetInstance)
	{
		UE_LOG(LogTemplateSelectorPawn, Warning, TEXT("Failed to create MainMenuWidgetInstance"));
		return;
	}

	if (MainMenuWidgetInstance->MediaPlayer)
	{
		UFileMediaSource* FileMediaSource = NewObject<UFileMediaSource>();
		FileMediaSource->FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Content/Movies/OpeningMovieRollerRacer.mp4"));
		MainMenuWidgetInstance->MediaPlayer->OpenSource(FileMediaSource);
		MainMenuWidgetInstance->MediaPlayer->Play();
	}

	MainMenuWidgetInstance->AddToViewport();

	GameInstance = Cast<URollerRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UMaterial* BaseMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/Movies/MyMediaTexture_Mat.MyMediaTexture_Mat"));
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	DynamicMaterialInstance->SetTextureParameterValue(FName("MyMediaTexture"), MainMenuWidgetInstance->MediaTexture);
	MainMenuWidgetInstance->MovieImage->SetBrushFromMaterial(DynamicMaterialInstance);

	if (Meshs.Num() > 0)
	{
		Mesh1->SetStaticMesh(Meshs[0]);
	}

	if (RacerMaterials.Num() > 0)
	{
		Mesh1->SetMaterial(0, RacerMaterials[0]);
	}

	Mesh1->SetVisibility(false);
	MainMenuWidgetInstance->ChangeNumberOfAIPlayersText(FString::FromInt(AIPlayerCount));
	MainMenuWidgetInstance->ChangeNumberOfLapsText(FString::FromInt(LapCount));

	if (LevelImages.Num() > 0)
	{
		MainMenuWidgetInstance->SetTrackSelectionImage(LevelImages[0]);
	}

	if (IntroWave)
	{
		IntroAudio = UGameplayStatics::SpawnSound2D(this, IntroWave, 1.0f, 1.0f, 0.0f, nullptr, true);
		if (IntroAudio)
		{
			IntroAudio->SetVolumeMultiplier(1.0f);
		}
	}
}

void APlayerSelectorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MainMenuWidgetInstance)
	{
		return;
	}

	const auto MovieImageVisibility = MainMenuWidgetInstance->MovieImage->GetVisibility();

	if (MovieImageVisibility == ESlateVisibility::Visible)
	{
		MainMenuWidgetInstance->HighlightStartMenuText(TextCount);
		return; 
	}

	if (MovieImageVisibility == ESlateVisibility::Hidden)
	{
		const bool bSelectRacerVisible = (MainMenuWidgetInstance->SelectRacerTextBlock->GetVisibility() == ESlateVisibility::Visible);
		const bool bSelectTrackVisible = (MainMenuWidgetInstance->SelectTrackTextBlock->GetVisibility() == ESlateVisibility::Visible);

		if (bSelectRacerVisible)
		{
			MainMenuWidgetInstance->HighlightRacerSelectionText(TextCount);

			bool bRacerTextBold = (MainMenuWidgetInstance->SelectRacerTextBlock->Font.TypefaceFontName == FName("Bold"));
			bool bRacerDesignBold = (MainMenuWidgetInstance->SelectRacerDesignTextBlock->Font.TypefaceFontName == FName("Bold"));

			if (bRacerTextBold || bRacerDesignBold)
			{
				SetArrowVisibilityIfChanged(ESlateVisibility::Visible);
				if (!Mesh1->IsVisible())
				{
					Mesh1->SetVisibility(true);
				}
			}
			else
			{
				SetArrowVisibilityIfChanged(ESlateVisibility::Hidden);
				if (Mesh1->IsVisible())
				{
					Mesh1->SetVisibility(false);
				}
			}
		}
		else if (bSelectTrackVisible)
		{
			MainMenuWidgetInstance->HighlightTrackSelectionText(TextCount);

			bool bTrackBold = (MainMenuWidgetInstance->SelectTrackTextBlock->Font.TypefaceFontName == FName("Bold"));
			bool bNumberOfComputerBold = (MainMenuWidgetInstance->SelectNumberOfComputerTextBlock->Font.TypefaceFontName == FName("Bold"));
			bool bNumberOfLapsBold = (MainMenuWidgetInstance->SelectNumberOfLapsTextBlock->Font.TypefaceFontName == FName("Bold"));

			if (bTrackBold)
			{
				MainMenuWidgetInstance->TrackSelectionImage->SetVisibility(ESlateVisibility::Visible);
				SetArrowVisibilityIfChanged(ESlateVisibility::Visible);
			}
			else
			{
				MainMenuWidgetInstance->TrackSelectionImage->SetVisibility(ESlateVisibility::Hidden);
			}

			if (bNumberOfComputerBold)
			{
				MainMenuWidgetInstance->PlayerChosenAIPlayerTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->LeftArrowImage->SetVisibility(AIPlayerCount <= 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
				MainMenuWidgetInstance->RightArrowImage->SetVisibility(AIPlayerCount >= MaxAIPlayerValue ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
			}
			else
			{
				MainMenuWidgetInstance->PlayerChosenAIPlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
			}

			if (bNumberOfLapsBold)
			{
				MainMenuWidgetInstance->PlayerChosenNumberOfLapsTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->LeftArrowImage->SetVisibility(LapCount <= 1 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
				MainMenuWidgetInstance->RightArrowImage->SetVisibility(LapCount >= MaxLapCount ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
			}
			else
			{
				MainMenuWidgetInstance->PlayerChosenNumberOfLapsTextBlock->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void APlayerSelectorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemplateSelectorPawn, Warning, TEXT("No player controller available during SetupPlayerInputComponent"));
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ConfirmSelectionAction)
			EnhancedInputComponent->BindAction(ConfirmSelectionAction, ETriggerEvent::Triggered, this, &APlayerSelectorPawn::ConfirmSelection);

		if (LeftRightSelectorAction)
			EnhancedInputComponent->BindAction(LeftRightSelectorAction, ETriggerEvent::Triggered, this, &APlayerSelectorPawn::LeftRightSelector);

		if (UpDownSelectorAction)
			EnhancedInputComponent->BindAction(UpDownSelectorAction, ETriggerEvent::Triggered, this, &APlayerSelectorPawn::UpDownSelector);

		if (BackAction)
			EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Triggered, this, &APlayerSelectorPawn::Back);
	}
	else
	{
		UE_LOG(LogTemplateSelectorPawn, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system."), *GetNameSafe(this));
	}
}

void APlayerSelectorPawn::LeftRightSelector(const FInputActionValue& Value)
{
	float FloatValue = Value.Get<float>();
	if (!MainMenuWidgetInstance || MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Visible)
	{
		return;
	}

	if (MainMenuWidgetInstance->SelectRacerTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		if (MainMenuWidgetInstance->SelectRacerTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0)
			{
				CurrentMeshCount = (CurrentMeshCount + 1) % Meshs.Num();
			}
			else if (FloatValue < 0)
			{
				CurrentMeshCount = (CurrentMeshCount == 0) ? Meshs.Num() - 1 : CurrentMeshCount - 1;
			}
			Mesh1->SetStaticMesh(Meshs[CurrentMeshCount]);
		}
		else if (MainMenuWidgetInstance->SelectRacerDesignTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0)
			{
				MaterialCount = (MaterialCount + 1) % RacerMaterials.Num();
			}
			else if (FloatValue < 0)
			{
				MaterialCount = (MaterialCount == 0) ? RacerMaterials.Num() - 1 : MaterialCount - 1;
			}
			Mesh1->SetMaterial(0, RacerMaterials[MaterialCount]);
		}
	}
	else if (MainMenuWidgetInstance->SelectTrackTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		if (MainMenuWidgetInstance->SelectTrackTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0)
			{
				CurrentTrackCount = (CurrentTrackCount + 1) % LevelImages.Num();
			}
			else if (FloatValue < 0)
			{
				CurrentTrackCount = (CurrentTrackCount == 0) ? LevelImages.Num() - 1 : CurrentTrackCount - 1;
			}
			MainMenuWidgetInstance->SetTrackSelectionImage(LevelImages[CurrentTrackCount]);
		}
		else if (MainMenuWidgetInstance->SelectNumberOfComputerTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0 && AIPlayerCount < MaxAIPlayerValue)
			{
				AIPlayerCount++;
			}
			else if (FloatValue < 0 && AIPlayerCount > 0)
			{
				AIPlayerCount--;
			}
			MainMenuWidgetInstance->ChangeNumberOfAIPlayersText(FString::FromInt(AIPlayerCount));
		}
		else if (MainMenuWidgetInstance->SelectNumberOfLapsTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0 && LapCount < MaxLapCount)
			{
				LapCount++;
			}
			else if (FloatValue < 0 && LapCount > 1)
			{
				LapCount--;
			}
			MainMenuWidgetInstance->ChangeNumberOfLapsText(FString::FromInt(LapCount));
		}
	}
}

void APlayerSelectorPawn::UpDownSelector(const FInputActionValue& Value)
{
	float FloatValue = Value.Get<float>();
	if (!MainMenuWidgetInstance)
	{
		return;
	}

	const ESlateVisibility MovieVisibility = MainMenuWidgetInstance->MovieImage->GetVisibility();
	if (MovieVisibility == ESlateVisibility::Visible)
	{
		if (FloatValue > 0)
		{
			if (TextCount > 0)
			{
				--TextCount;
			}
		}
		else if (FloatValue < 0)
		{
			if (TextCount < MainMenuWidgetInstance->StartMenuTextList.Num() - 1)
			{
				++TextCount;
			}
		}
		return;
	}

	if (MovieVisibility == ESlateVisibility::Hidden)
	{
		if (MainMenuWidgetInstance->SelectRacerTextBlock->GetVisibility() == ESlateVisibility::Visible)
		{
			if (FloatValue > 0 && TextCount > 0)
			{
				--TextCount;
			}
			else if (FloatValue < 0 && TextCount < MainMenuWidgetInstance->RacerSelectionTextList.Num() - 1)
			{
				++TextCount;
			}
			return;
		}

		if (MainMenuWidgetInstance->SelectTrackTextBlock->GetVisibility() == ESlateVisibility::Visible)
		{
			if (FloatValue > 0 && TextCount > 0)
			{
				--TextCount;
			}
			else if (FloatValue < 0 && TextCount < MainMenuWidgetInstance->TrackSelectionTextList.Num() - 1)
			{
				++TextCount;
			}
			return;
		}
	}
}

void APlayerSelectorPawn::ConfirmSelection(const FInputActionValue& Value)
{
	if (!MainMenuWidgetInstance)
	{
		return;
	}

	const bool bMovieVisible = (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Visible);

	if (bMovieVisible)
	{
		if (MainMenuWidgetInstance->SinglePlayerTextBlock->GetVisibility() == ESlateVisibility::Hidden)
		{
			MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Visible);
			TextCount = 0;
			MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->ConfirmTextBlock->SetVisibility(ESlateVisibility::Hidden);
			return;
		}

		const FName SinglePlayerFont = MainMenuWidgetInstance->SinglePlayerTextBlock->Font.TypefaceFontName;
		const FName MultiPlayerFont = MainMenuWidgetInstance->MultiplayerTextBlock->Font.TypefaceFontName;
		const FName CreditsFont = MainMenuWidgetInstance->CreditsTextBlock->Font.TypefaceFontName;
		const FName ExitFont = MainMenuWidgetInstance->ExitTextBlock->Font.TypefaceFontName;

		if (SinglePlayerFont == FName("Bold"))
		{
			HideMainMenuOptions();
			MainMenuWidgetInstance->MediaPlayer->Pause();
			MainMenuWidgetInstance->MovieImage->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->SelectRacerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->SelectRacerDesignTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Visible);
			TextCount = 0;
			return;
		}

		if (MultiPlayerFont == FName("Bold"))
		{
			HideMainMenuOptions();
			MainMenuWidgetInstance->MediaPlayer->Pause();
			MainMenuWidgetInstance->MovieImage->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->ComingSoonTextBlock->SetVisibility(ESlateVisibility::Visible);
			return;
		}

		if (CreditsFont == FName("Bold"))
		{
			MainMenuWidgetInstance->MediaPlayer->Pause();
			MainMenuWidgetInstance->MovieImage->SetVisibility(ESlateVisibility::Hidden);
			HideMainMenuOptions();
			MainMenuWidgetInstance->ComingSoonTextBlock->SetVisibility(ESlateVisibility::Visible);
			return;
		}

		if (ExitFont == FName("Bold"))
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
			return;
		}
		return;
	}
	
	if (MainMenuWidgetInstance->SelectRacerTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		TextCount = 0;
		MainMenuWidgetInstance->SelectRacerTextBlock->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidgetInstance->SelectRacerDesignTextBlock->SetVisibility(ESlateVisibility::Hidden);

		MainMenuWidgetInstance->SelectTrackTextBlock->SetVisibility(ESlateVisibility::Visible);
		MainMenuWidgetInstance->SelectNumberOfComputerTextBlock->SetVisibility(ESlateVisibility::Visible);
		MainMenuWidgetInstance->SelectNumberOfLapsTextBlock->SetVisibility(ESlateVisibility::Visible);
		MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Visible);

		if (GameInstance)
		{
			GameInstance->StaticMesh = Meshs[CurrentMeshCount];
			GameInstance->Material = RacerMaterials[MaterialCount];
		}
		Mesh1->SetVisibility(false);
		return;
	}

	if (MainMenuWidgetInstance->SelectTrackTextBlock->GetVisibility() == ESlateVisibility::Visible)
	{
		UWorld* World = GetWorld();
		if (!World)
		{
			UE_LOG(LogTemplateSelectorPawn, Warning, TEXT("No world found during ConfirmSelection"));
			return;
		}
		if (GameInstance)
		{
			GameInstance->AIRacerNumber = AIPlayerCount;
			GameInstance->NumberOfLaps = LapCount;
		}

		const FString LevelImageName = LevelImages[CurrentTrackCount]->GetName();
		const FString LoadLevelName = LevelImageName.Replace(TEXT("Image"), TEXT(""));
		UGameplayStatics::OpenLevel(World, FName(LoadLevelName));
		return;
	}
}

void APlayerSelectorPawn::Back(const FInputActionValue& Value)
{
	if (!MainMenuWidgetInstance)
	{
		return;
	}

	const bool bMovieVisible = (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Visible);

	if (!bMovieVisible)
	{
		if (MainMenuWidgetInstance->SelectRacerTextBlock->GetVisibility() == ESlateVisibility::Visible)
		{
			MainMenuWidgetInstance->MovieImage->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->MediaPlayer->Play();

			MainMenuWidgetInstance->SelectRacerTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->SelectRacerDesignTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->LeftArrowImage->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->RightArrowImage->SetVisibility(ESlateVisibility::Hidden);

			Mesh1->SetVisibility(false);

			MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Visible);
			return;
		}
		else if (MainMenuWidgetInstance->ComingSoonTextBlock->GetVisibility() == ESlateVisibility::Visible)
		{
			MainMenuWidgetInstance->MovieImage->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->MediaPlayer->Play();

			MainMenuWidgetInstance->ComingSoonTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->ConfirmTextBlock->SetVisibility(ESlateVisibility::Visible);
			return;
		}
		else if (MainMenuWidgetInstance->SelectTrackTextBlock->GetVisibility() == ESlateVisibility::Visible)
		{
			MainMenuWidgetInstance->SelectTrackTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->SelectNumberOfComputerTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->SelectNumberOfLapsTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->TrackSelectionImage->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->PlayerChosenAIPlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->PlayerChosenNumberOfLapsTextBlock->SetVisibility(ESlateVisibility::Hidden);

			MainMenuWidgetInstance->SelectRacerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->SelectRacerDesignTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->LeftArrowImage->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->RightArrowImage->SetVisibility(ESlateVisibility::Visible);
			Mesh1->SetVisibility(true);
			return;
		}
	}
	else
	{
		MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidgetInstance->ConfirmTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerSelectorPawn::SetArrowVisibilityIfChanged(ESlateVisibility NewVisibility)
{
	if (MainMenuWidgetInstance->LeftArrowImage->GetVisibility() != NewVisibility)
	{
		MainMenuWidgetInstance->LeftArrowImage->SetVisibility(NewVisibility);
	}
	if (MainMenuWidgetInstance->RightArrowImage->GetVisibility() != NewVisibility)
	{
		MainMenuWidgetInstance->RightArrowImage->SetVisibility(NewVisibility);
	}
}

void APlayerSelectorPawn::HideMainMenuOptions()
{
	if (!MainMenuWidgetInstance)
	{
		return;
	}
	MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidgetInstance->ConfirmTextBlock->SetVisibility(ESlateVisibility::Hidden);
}