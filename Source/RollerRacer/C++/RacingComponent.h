// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SplineTrack.h"
#include "RacingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLERRACER_API URacingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle OverTheEdgeTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CheckActorOnFloor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ActorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* OwnerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* OwnerSplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* OwnerSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* OwnerSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MoveForce;

	UPROPERTY()
	FVector Gravity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ForwardMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool SlowDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentLapNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ForwardCheckPointCounter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BackwardCheckPointCounter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalDistanceTravelled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsMovingForward = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float NextCheckPointDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PreviousCheckPointCounter;

	float RadiusValue;

protected:

public:	
	bool LineTraceToTrack(FHitResult& HitResult, int32 LengthOfTrace);

	void CheckActorAboveFloor();

	void AdvanceTimer();

	void PlaceActorBackOnFloor(float Distance);

	float GetDistance(FVector Location);

	void PassInfoFromParent(UStaticMeshComponent* Mesh, USplineComponent* SplineComponent,
		USceneComponent* SceneComponent, AActor* Actor, USpringArmComponent* SpringArm);

	void SetForwardAndDownVelocity(float Distance, USplineComponent* SplineComponent, USpringArmComponent* SpringArm, UStaticMeshComponent* Mesh);

	void TrackPlayerProgress(float Distance);
};
