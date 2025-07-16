// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CaptureTextureSnapshot.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameStartWidget.h"
#include "RollerRacerGameInstance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "PlayerSelectorPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateSelectorPawn, Log, All);

UCLASS()
class ROLLERRACER_API APlayerSelectorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerSelectorPawn();

	/** Ball mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*> Meshs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UMaterial*> RacerMaterials;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UTexture2D*> LevelImages;

	UPROPERTY()
	int32 CurrentMeshCount;

	UPROPERTY()
	int32 CurrentTrackCount;

	UPROPERTY()
	int32 AIPlayerCount;
	
	UPROPERTY()
	int32 MaxAIPlayerValue;

	UPROPERTY()
	int32 LapCount;

	UPROPERTY()
	int32 MaxLapCount;

	UPROPERTY()
	int32 TextCount;

	UPROPERTY()
	int32 MaterialCount;

	UPROPERTY()
	bool MoviePlaying = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
	TSubclassOf<class UGameStartWidget> WidgetClass;

	UPROPERTY()
	UGameStartWidget* MainMenuWidgetInstance;

	UPROPERTY()
	UCaptureTextureSnapshot* CaptureTexture;

	UPROPERTY()
	URollerRacerGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LeftRightSelectorAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UpDownSelectorAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ConfirmSelectionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BackAction;

	UPROPERTY()
	UTexture2D* PlayerTexture;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundWave* IntroWave;

	UPROPERTY()
	UAudioComponent* IntroAudio;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LeftRightSelector(const FInputActionValue& Value);

	void UpDownSelector(const FInputActionValue& Value);

	void ConfirmSelection(const FInputActionValue& Value);

	void Back(const FInputActionValue& Value);

	void SetArrowVisibilityIfChanged(ESlateVisibility NewVisibility);

	void HideMainMenuOptions();

};
