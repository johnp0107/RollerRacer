// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSelectorPawn.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetMathLibrary.h"

#define LOCTEXT_NAMESPACE "SelectorPawn"

DEFINE_LOG_CATEGORY(LogTemplateSelectorPawn);

// Sets default values
APlayerSelectorPawn::APlayerSelectorPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh1");
	Mesh1->SetSimulatePhysics(true);
	Mesh1->SetEnableGravity(false);
	SetRootComponent(Mesh1);
	/*Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh2");
	Mesh2->SetSimulatePhysics(true);
	Mesh2->SetEnableGravity(false);
	Mesh2->SetupAttachment(RootComponent);
	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh3");
	Mesh3->SetSimulatePhysics(true);
	Mesh3->SetEnableGravity(false);
	Mesh3->SetupAttachment(RootComponent);*/

	// Create the SpringArm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh1);
	SpringArm->TargetArmLength = 700;
	SpringArm->SocketOffset.Z = 200;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 3;

	// Create the Camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	CaptureTexture = CreateDefaultSubobject<UCaptureTextureSnapshot>(TEXT("CaptureTexture"));
}

// Called when the game starts or when spawned
void APlayerSelectorPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentMeshCount = 0;
	MaterialCount = 0;
	MaxAIPlayerValue = 7;
	float TargetPitch = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), Mesh1->GetComponentLocation()).Pitch;
	Camera->SetWorldRotation(FRotator(TargetPitch, Camera->GetComponentRotation().Yaw, Camera->GetComponentRotation().Roll));

	if (WidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UGameStartWidget>(GetWorld(), WidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			MainMenuWidgetInstance->MediaPlayer->Play();
		}
	}
	GameInstance = Cast<URollerRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UMaterial* BaseMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/Movies/MyMediaTexture_Mat.MyMediaTexture_Mat"));
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
	DynamicMaterialInstance->SetTextureParameterValue(FName("MyMediaTexture"), MainMenuWidgetInstance->MediaTexture);
	MainMenuWidgetInstance->MovieImage->SetBrushFromMaterial(DynamicMaterialInstance);

	//RacerSelectorTextList.Add("Select Racer");
	//RacerSelectorTextList.Add("Select Racer Design");
	//RacerSelectorTextList.Add("Select Track");
	//RacerSelectorTextList.Add("Select Number of Computer Racers");

	/*RacerSelectorTextList.Add("Select Racer");
	RacerSelectorTextList.Add("Select Racer Design");
	RacerSelectorTextList.Add("Select Track");
	RacerSelectorTextList.Add("Select Number of Computer Racers");*/
	Mesh1->SetVisibility(false);
	/*Mesh2->SetVisibility(false);
	Mesh3->SetVisibility(false);*/

	/*Mesh2->SetRelativeLocation(FVector(400, 400, 0));
	Mesh3->SetRelativeLocation(FVector(400, -400, 0));*/


	Mesh1->SetStaticMesh(Meshs[0]);
	Mesh1->SetMaterial(0, RacerMaterials[0]);
	/*Mesh2->SetStaticMesh(Meshs[1]);
	Mesh2->SetMaterial(0, RacerMaterials[1]);
	Mesh3->SetStaticMesh(Meshs[2]);
	Mesh3->SetMaterial(0, RacerMaterials[2]);*/
	//MainMenuWidgetInstance->ChangeSelectorText(RacerSelectorTextList[TextCount]);

	AIPlayerCount = 0;
	MainMenuWidgetInstance->ChangeNumberOfAIPlayersText(FString::FromInt(AIPlayerCount));
	MainMenuWidgetInstance->SetTrackSelectionImage(LevelImages[0]);

	/*Mesh2Count = CurrentMeshCount + 1;
	Mesh3Count = Meshs.Num() - 1;*/

	//Material2Count = MaterialCount + 1;
	//Material3Count = RacerMaterials.Num() - 1;

	/*FLinearColor LinearColor;
	RacerMaterials[Material2Count]->GetVectorParameterValue(FName("Color Value"), LinearColor);
	MainMenuWidgetInstance->LeftArrowImage->SetBrushTintColor(LinearColor);
	MainMenuWidgetInstance->RightArrowImage->SetBrushTintColor(LinearColor);
	MainMenuWidgetInstance->UpArrowImage->SetBrushTintColor(LinearColor);
	MainMenuWidgetInstance->DownArrowImage->SetBrushTintColor(LinearColor);
	MainMenuWidgetInstance->TextSelector->SetColorAndOpacity(LinearColor);
	MainMenuWidgetInstance->PressStartTextBlock->SetColorAndOpacity(LinearColor);
	MainMenuWidgetInstance->GameTitleTextBlock->SetColorAndOpacity(LinearColor);*/
}

void APlayerSelectorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Visible)
	{
		MainMenuWidgetInstance->HighlightStartMenuText(TextCount);
	}


	if (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Hidden)
	{
		MainMenuWidgetInstance->HighlightRaceSelectionText(TextCount);

		if (MainMenuWidgetInstance->SelectRacerTextBlock->Font.TypefaceFontName == FName("Bold") ||
			MainMenuWidgetInstance->SelectRacerDesignTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			Mesh1->SetVisibility(true);
			/*Mesh2->SetVisibility(true);
			Mesh3->SetVisibility(true);*/
		}
		else
		{
			Mesh1->SetVisibility(false);
			/*Mesh2->SetVisibility(false);
			Mesh3->SetVisibility(false);*/
		}
		if (MainMenuWidgetInstance->SelectTrackTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			MainMenuWidgetInstance->TrackSelectionImage->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->LeftArrowImage->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->RightArrowImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			MainMenuWidgetInstance->TrackSelectionImage->SetVisibility(ESlateVisibility::Hidden);
		}
		if (MainMenuWidgetInstance->AIRacerNumberTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			MainMenuWidgetInstance->NumberOfAIPlayers->SetVisibility(ESlateVisibility::Visible);
			if (AIPlayerCount <= 0)
			{
				MainMenuWidgetInstance->LeftArrowImage->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				MainMenuWidgetInstance->LeftArrowImage->SetVisibility(ESlateVisibility::Visible);
			}
			if (AIPlayerCount >= MaxAIPlayerValue)
			{
				MainMenuWidgetInstance->RightArrowImage->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				MainMenuWidgetInstance->RightArrowImage->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			MainMenuWidgetInstance->NumberOfAIPlayers->SetVisibility(ESlateVisibility::Hidden);
		}

		/*if (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Hidden)
		{
			if (TextCount <= 0)
			{
				MainMenuWidgetInstance->UpArrowImage->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				MainMenuWidgetInstance->UpArrowImage->SetVisibility(ESlateVisibility::Visible);
			}
			if (TextCount >= RacerSelectorTextList.Num() - 1)
			{
				MainMenuWidgetInstance->DownArrowImage->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->UpArrowImage->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->DownArrowImage->SetRenderTransformAngle(180);
			}
			else
			{
				MainMenuWidgetInstance->DownArrowImage->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->DownArrowImage->SetRenderTransformAngle(0);
			}
		}
		else
		{
			MainMenuWidgetInstance->UpArrowImage->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidgetInstance->DownArrowImage->SetVisibility(ESlateVisibility::Hidden);
		}*/
	}
}

// Called to bind functionality to input
void APlayerSelectorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Start Action
		EnhancedInputComponent->BindAction(StartAction, ETriggerEvent::Triggered, this, &APlayerSelectorPawn::Start);

		EnhancedInputComponent->BindAction(LeftRightSelectorAction, ETriggerEvent::Triggered, this, &APlayerSelectorPawn::LeftRightSelector);

		EnhancedInputComponent->BindAction(UpDownSelectorAction, ETriggerEvent::Triggered, this, &APlayerSelectorPawn::UpDownSelector);
	}
	else
	{
		UE_LOG(LogTemplateSelectorPawn, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerSelectorPawn::LeftRightSelector(const FInputActionValue& Value)
{
	double FloatValue = Value.Get<float>();
	if (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Hidden)
	{
		if (MainMenuWidgetInstance->SelectRacerTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0)
			{
				if (CurrentMeshCount < Meshs.Num() - 1)
				{
					CurrentMeshCount++;
				}
				else
				{
					CurrentMeshCount = 0;
				}
				/*if (Mesh2Count < Meshs.Num() - 1)
				{
					Mesh2Count++;
				}
				else
				{
					Mesh2Count = 0;
				}
				if (Mesh3Count < Meshs.Num() - 1)
				{
					Mesh3Count++;
				}
				else
				{
					Mesh3Count = 0;
				}*/
			}
			else if (FloatValue < 0)
			{
				if (CurrentMeshCount > 0)
				{
					CurrentMeshCount--;
				}
				else
				{
					CurrentMeshCount = Meshs.Num() - 1;
				}
				/*if (Mesh2Count > 0)
				{
					Mesh2Count--;
				}
				else
				{
					Mesh2Count = Meshs.Num() - 1;
				}
				if (Mesh3Count > 0)
				{
					Mesh3Count--;
				}
				else
				{
					Mesh3Count = Meshs.Num() - 1;
				}*/
			}
			Mesh1->SetStaticMesh(Meshs[CurrentMeshCount]);
			/*Mesh2->SetStaticMesh(Meshs[Mesh2Count]);
			Mesh3->SetStaticMesh(Meshs[Mesh3Count]);*/
		}
		else if (MainMenuWidgetInstance->SelectRacerDesignTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0)
			{
				if (MaterialCount < RacerMaterials.Num() - 1)
				{
					MaterialCount++;
				}
				else
				{
					MaterialCount = 0;
				}
				/*	if (Material2Count < RacerMaterials.Num() - 1)
					{
						Material2Count++;
					}
					else
					{
						Material2Count = 0;
					}*/
					/*if (Material3Count < RacerMaterials.Num() - 1)
					{
						Material3Count++;
					}
					else
					{
						Material3Count = 0;
					}*/
			}
			else if (FloatValue < 0)
			{
				if (MaterialCount > 0)
				{
					MaterialCount--;
				}
				else
				{
					MaterialCount = RacerMaterials.Num() - 1;
				}
				/*if (Material2Count > 0)
				{
					Material2Count--;
				}
				else
				{
					Material2Count = RacerMaterials.Num() - 1;
				}*/
				/*if (Material3Count > 0)
				{
					Material3Count--;
				}
				else
				{
					Material3Count = RacerMaterials.Num() - 1;
				}*/
			}
			Mesh1->SetMaterial(0, RacerMaterials[MaterialCount]);
			/*FLinearColor LinearColor;
			RacerMaterials[Material2Count]->GetVectorParameterValue(FName("Color Value"), LinearColor);
			MainMenuWidgetInstance->LeftArrowImage->SetBrushTintColor(LinearColor);
			MainMenuWidgetInstance->RightArrowImage->SetBrushTintColor(LinearColor);
			MainMenuWidgetInstance->UpArrowImage->SetBrushTintColor(LinearColor);
			MainMenuWidgetInstance->DownArrowImage->SetBrushTintColor(LinearColor);
			MainMenuWidgetInstance->TextSelector->SetColorAndOpacity(LinearColor);
			MainMenuWidgetInstance->PressStartTextBlock->SetColorAndOpacity(LinearColor);
			MainMenuWidgetInstance->GameTitleTextBlock->SetColorAndOpacity(LinearColor);*/
			/*Mesh2->SetMaterial(0, RacerMaterials[Material2Count]);
			Mesh3->SetMaterial(0, RacerMaterials[Material3Count]);*/
		}
		else if (MainMenuWidgetInstance->SelectTrackTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0)
			{
				if (CurrentTrackCount < LevelImages.Num() - 1)
				{
					CurrentTrackCount++;
				}
				else
				{
					CurrentTrackCount = 0;
				}
			}
			else if (FloatValue < 0)
			{
				if (CurrentTrackCount > 0)
				{
					CurrentTrackCount--;
				}
				else
				{
					CurrentTrackCount = LevelImages.Num() - 1;
				}
			}
			MainMenuWidgetInstance->SetTrackSelectionImage(LevelImages[CurrentTrackCount]);
		}
		else if (MainMenuWidgetInstance->AIRacerNumberTextBlock->Font.TypefaceFontName == FName("Bold"))
		{
			if (FloatValue > 0)
			{
				if (AIPlayerCount < MaxAIPlayerValue)
				{
					AIPlayerCount++;
				}
			}
			else if (FloatValue < 0)
			{
				if (AIPlayerCount > 0)
				{
					AIPlayerCount--;
				}
			}
			MainMenuWidgetInstance->ChangeNumberOfAIPlayersText(FString::SanitizeFloat(AIPlayerCount));
		}
	}
}

void APlayerSelectorPawn::UpDownSelector(const FInputActionValue& Value)
{
	double FloatValue = Value.Get<float>();
	if (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Visible)
	{
		if (FloatValue > 0)
		{
			if (TextCount > 0)
			{
				TextCount--;
			}
		}
		else if (TextCount < MainMenuWidgetInstance->StartMenuTextList.Num())
		{
			if (FloatValue < 0)
			{
				TextCount++;
			}
		}
	}

	if (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Hidden)
	{
		if (FloatValue > 0)
		{
			if (TextCount > 0)
			{
				TextCount--;
			}
		}
		else if (TextCount < MainMenuWidgetInstance->RaceSelectionTextList.Num())
		{
			if (FloatValue < 0)
			{
				TextCount++;
			}
		}
		//MainMenuWidgetInstance->ChangeSelectorText(RacerSelectorTextList[TextCount]);
	}
}

void APlayerSelectorPawn::Start(const FInputActionValue& Value)
{

	if (MainMenuWidgetInstance->MovieImage->GetVisibility() == ESlateVisibility::Visible)
	{
		if (MainMenuWidgetInstance->SinglePlayerTextBlock->GetVisibility() == ESlateVisibility::Hidden)
		{
			MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Visible);
			TextCount = 0;

			MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if (MainMenuWidgetInstance->SinglePlayerTextBlock->Font.TypefaceFontName == FName("Bold"))
			{
				MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Hidden);

				MainMenuWidgetInstance->MediaPlayer->Pause();
				MainMenuWidgetInstance->MovieImage->SetVisibility(ESlateVisibility::Hidden);
				
				/*MainMenuWidgetInstance->TextSelector->SetVisibility(ESlateVisibility::Visible);*/
				MainMenuWidgetInstance->SelectRacerTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->SelectRacerDesignTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->SelectTrackTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->AIRacerNumberTextBlock->SetVisibility(ESlateVisibility::Visible);

				//MainMenuWidgetInstance->LeftArrowImage->SetVisibility(ESlateVisibility::Visible);
				//MainMenuWidgetInstance->RightArrowImage->SetVisibility(ESlateVisibility::Visible);

				/*RacerSelectorTextList[0] = "Select Racer";
				RacerSelectorTextList[1] = "Select Racer Design";
				RacerSelectorTextList[2] = "Select Track";
				RacerSelectorTextList[3] = "Select Number of Computer Racers";*/
				
				//MainMenuWidgetInstance->BackTextBlock->SetText(FText::FromString(TEXT("Press Start to start race")));
				MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Visible);
			}
			else if (MainMenuWidgetInstance->MultiplayerTextBlock->Font.TypefaceFontName == FName("Bold"))
			{
				MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Hidden);

				MainMenuWidgetInstance->MediaPlayer->Pause();
				MainMenuWidgetInstance->MovieImage->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->BackTextBlock->SetVisibility(ESlateVisibility::Hidden);
				//MainMenuWidgetInstance->TextSelector->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->SelectRacerTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->SelectRacerDesignTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->SelectTrackTextBlock->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->AIRacerNumberTextBlock->SetVisibility(ESlateVisibility::Visible);

				/*MainMenuWidgetInstance->LeftArrowImage->SetVisibility(ESlateVisibility::Visible);
				MainMenuWidgetInstance->RightArrowImage->SetVisibility(ESlateVisibility::Visible);*/
			}
			else if (MainMenuWidgetInstance->CreditsTextBlock->Font.TypefaceFontName == FName("Bold"))
			{
				MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Hidden);
			}
			else if (MainMenuWidgetInstance->ExitTextBlock->Font.TypefaceFontName == FName("Bold"))
			{
				MainMenuWidgetInstance->SinglePlayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->MultiplayerTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->CreditsTextBlock->SetVisibility(ESlateVisibility::Hidden);
				MainMenuWidgetInstance->ExitTextBlock->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	else
	{
		GameInstance->StaticMesh = Meshs[CurrentMeshCount];
		GameInstance->Material = RacerMaterials[MaterialCount];

		//TextCount = 0;
		/*MainMenuWidgetInstance->ChangeSelectorText(RacerSelectorTextList[TextCount]);
		MainMenuWidgetInstance->SetTrackSelectionImage(LevelImages[CurrentTrackCount]);*/

		UWorld* World = GetWorld();
		GameInstance->AIRacerNumber = AIPlayerCount;

		FString LevelImageName = LevelImages[CurrentTrackCount]->GetName();
		FString LoadLevelName = LevelImageName.Replace(TEXT("Image"), TEXT(""));
		UGameplayStatics::OpenLevel(World, FName(LoadLevelName));
	}
}

