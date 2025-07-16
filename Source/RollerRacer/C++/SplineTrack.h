// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "RaceTrackingWidget.h"
#include "SplineTrack.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateAIRollerRacerPawn, Log, All);

UCLASS()
class ROLLERRACER_API ASplineTrack : public AActor
{
	GENERATED_BODY()
	
public:	
	ASplineTrack();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, Category = "Spline")
	USplineComponent* SplineComponent;

	UPROPERTY(VisibleAnywhere, Category = "Spline")
	USplineComponent* OutsideSplineComponent;

	UPROPERTY(VisibleAnywhere, Category = "Spline")
	USplineComponent* InsideSplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	FVector BoundingBoxDifference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TArray<USplineMeshComponent*> SplineMeshArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool AddSplineTrackToArray = false;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
