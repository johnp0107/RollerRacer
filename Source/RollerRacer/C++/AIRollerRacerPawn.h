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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 NextPointDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<USplineComponent*> SplinePointArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 SplineTrackSelector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SplineCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector SplineLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalDistanceTravelled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AheadDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxSpeed;

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

	UPROPERTY()
	int32 CurrentSplineCount;

	float NewDistance;

	float Difference;

	int32 NumLapsCompleted;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle OutOfSpeedZoneTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TurnToSplinePoint(float DeltaTime);

	void Steering(float TurnValue);

	void Accelerate(float AccelerationDirectionValue);

	void SlowDown();

	void OutOfSpeedZoneTimer();

	void ResetMaxSpeed();
};
