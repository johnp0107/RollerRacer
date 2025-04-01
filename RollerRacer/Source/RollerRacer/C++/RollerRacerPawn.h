// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SplineTrack.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "RaceTrackingWidget.h"
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
	FTimerHandle DisplayGoTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalDistanceTravelled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTexture2D*> ActorTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
	TSubclassOf<class URaceTrackingWidget> WidgetClass;

	UPROPERTY()
	URaceTrackingWidget* RacePositionWidgetInstance;

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

	//void AdjustCameraHeight();

	//void AdjustCameraRoll();

	//void SetForwardDirection();

	//void CheckPlayerAboveFloor(float Distance);

	/*void PlacePlayerBackOnFloor(float Distance);*/

	/*void AdvanceTimer();*/

	void DisplayGoTimer();

	void ThreeSecondCountdownTimer();

	//void TrackPlayerProgress(float Distance);

	/*void SetForwardAndDownVelocity(float Distance);*/

	void UpdateRaceWidget(float Distance);

	//bool IsPlayerOnTrack(FHitResult& HitResult, int32 LengthOfTrace);

	/*float GetDistance(FVector MeshLocation);*/
};
