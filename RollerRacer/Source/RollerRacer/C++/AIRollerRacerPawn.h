// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "SplineTrack.h"
#include "CaptureTextureSnapshot.h"
#include "RacingComponent.h"
#include "RollerRacerGameMode.h"
#include "AIRollerRacerPawn.generated.h"

UCLASS()
class ROLLERRACER_API AAIRollerRacerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIRollerRacerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AIMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*> StaticMeshs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UMaterial*> Materials;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* AISpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USceneComponent* LevelSceneComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	//USceneComponent* GravitySceneComponent;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ForwardMovement;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinLevelHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector HitPoint;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 NextPointDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<USplineComponent*> SplinePointArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SplineTrackSelector;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector AILocation;*/

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CheckAIOnFloor = true;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SplineCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector SplineLocation;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CountDownTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle OverTheEdgeTimer;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NumLapsCompleted;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float NextCheckPointDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PreviousCheckPointCounter;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsMovingForward = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ForwardCheckPointCounter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BackwardCheckPointCounter;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalDistanceTravelled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AheadDistance;

	UPROPERTY()
	UCaptureTextureSnapshot* CaptureTexture;

	UPROPERTY()
	UTexture2D* AITexture;

	UPROPERTY()
	ASplineTrack* SplineActor;


	UPROPERTY()
	URacingComponent* RacingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ARollerRacerGameMode* RacerGameMode;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void AdjustLevelComponentHeight();

	/*void AdjustAIRoll();

	void SetForwardDirection();*/

	void TurnToSplinePoint(float DeltaTime);

	void Steering(float TurnValue);

	void Accelerate(float AccelerationDirectionValue);

	void SlowDown();

	/*void CheckAIAboveFloor();

	void PlaceAIBackOnFloor();

	void AdvanceTimer();

	void TrackAIProgress();

	void SetForwardAndDownVelocity();*/
};
