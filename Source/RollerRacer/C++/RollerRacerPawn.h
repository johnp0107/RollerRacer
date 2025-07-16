// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SplineTrack.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "RaceTrackingWidget.h"
#include "RaceOverWidget.h"
#include "CaptureTextureSnapshot.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "RacingComponent.h"
#include "RollerRacerGameMode.h"
#include "Camera/CameraComponent.h"
#include "RollerRacerGameInstance.h"
#include "RollerRacerPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateRollerRacerPawn, Log, All);

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class ROLLERRACER_API ARollerRacerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollerRacerPawn();

	/** Ball mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USceneComponent* LevelSceneComponent;

	/** Throttle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ThrottleAction;

	/** Steering Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SteeringAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UpDownSelectorAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ConfirmSelectionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BackAction;

	UPROPERTY()
	int32 TextCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ActorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* SplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ASplineTrack* SplineActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ARollerRacerGameMode* RacerGameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle ThreeSecondTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle OutOfSpeedZoneTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle DisplayGoTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalDistanceTravelled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTexture2D*> ActorTextures;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTexture2D*> FinishedRacerTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
	TSubclassOf<class URaceTrackingWidget> RaceTrackingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
	TSubclassOf<class URaceOverWidget> RaceOverWidgetClass;

	UPROPERTY()
	URaceTrackingWidget* RacePositionWidgetInstance;

	UPROPERTY()
	URaceOverWidget* RaceOverWidgetInstance;

	UPROPERTY()
	UCaptureTextureSnapshot* CaptureTexture;

	UPROPERTY()
	URacingComponent* RacingComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundWave* MySoundWave;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundWave* WrongWayWave;
	
	UPROPERTY()
	UAudioComponent* LevelAudio;

	UPROPERTY()
	UAudioComponent* WrongWayAudio;

	UPROPERTY()
	bool HideBackwardsDisplay = true;

	UPROPERTY()
	UTexture2D* PlayerTexture;

	UPROPERTY()
	URollerRacerGameInstance* GameInstance;

	int32 NumLapsCompleted;

	float AheadDistance;

	FVector SplineLocation;

	int32 MaxSpeed;

	float NewDistance;

	float Difference;
	
	float SplineCount;

	int32 NextPointDistance;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Throttle(const FInputActionValue& Value);

	void ReleaseThrottle(const FInputActionValue& Value);

	void Steering(const FInputActionValue& Value);

	void Pause(const FInputActionValue& Value);

	void UpDownSelector(const FInputActionValue& Value);

	void ConfirmSelection(const FInputActionValue& Value);

	void Back(const FInputActionValue& Value);

	void DisplayGoTimer();

	void ThreeSecondCountdownTimer();
	
	void OutOfSpeedZoneTimer();

	void UpdateRaceWidget(float Distance, float DeltaTime);

	void AutoDriving(float DeltaTime);

	void ResetMaxSpeed();

};
