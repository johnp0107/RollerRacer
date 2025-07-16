// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineTrack.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "RollerRacerPawn.h"
#include "TimerManager.h"
#include "AIRollerRacerPawn.h"


ASplineTrack::ASplineTrack()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	if (SplineComponent)
	{
		SetRootComponent(SplineComponent);
	}
	InsideSplineComponent = CreateDefaultSubobject<USplineComponent>("InsideSpline");
	InsideSplineComponent->SetupAttachment(RootComponent);
	OutsideSplineComponent = CreateDefaultSubobject<USplineComponent>("OutsideSpline");
	OutsideSplineComponent->SetupAttachment(RootComponent);
}

void ASplineTrack::BeginPlay()
{
	Super::BeginPlay();

	for (int32 SplineCount = 0; SplineCount < SplineComponent->GetNumberOfSplinePoints(); SplineCount++)
	{
		FVector MeshScale = SplineComponent->GetScaleAtSplinePoint(SplineCount);
		float Width = MeshScale.X * (BoundingBoxDifference.Y / 2 - 300);
		FVector SplineComponentLocation = SplineComponent->GetLocationAtSplinePoint(SplineCount, ESplineCoordinateSpace::Local);
		FVector SplineRightVector = SplineComponent->GetRightVectorAtSplinePoint(SplineCount, ESplineCoordinateSpace::Local) * (Width);

		if (OutsideSplineComponent->GetNumberOfSplinePoints() <= SplineCount)
		{
			OutsideSplineComponent->AddSplinePointAtIndex(SplineComponentLocation + SplineRightVector, SplineCount, ESplineCoordinateSpace::Local);
		}
		else
		{
			OutsideSplineComponent->SetLocationAtSplinePoint(SplineCount, SplineComponentLocation + SplineRightVector, ESplineCoordinateSpace::Local);
		}
		if (InsideSplineComponent->GetNumberOfSplinePoints() <= SplineCount)
		{
			InsideSplineComponent->AddSplinePointAtIndex(SplineComponentLocation - SplineRightVector, SplineCount, ESplineCoordinateSpace::Local);
		}
		else
		{
			InsideSplineComponent->SetLocationAtSplinePoint(SplineCount, SplineComponentLocation - SplineRightVector, ESplineCoordinateSpace::Local);
		}
	}
}

void ASplineTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASplineTrack::OnConstruction(const FTransform& Transform)
{
	SplineMeshArray.Empty();
	Super::OnConstruction(Transform);
	if (!Mesh)
	{
		return;
	}

	FBox MeshBoundingBox = Mesh->GetBoundingBox();
	FVector MeshBoxMin = MeshBoundingBox.Min;
	FVector MeshBoxMax = MeshBoundingBox.Max;
	BoundingBoxDifference = MeshBoxMax - MeshBoxMin;
	float Spacing = BoundingBoxDifference.X;

	int32 NumberOfInstances = UKismetMathLibrary::Round((SplineComponent->GetSplineLength() - 0.01) / Spacing);

	float StretchSize = (SplineComponent->GetSplineLength() / Spacing) / NumberOfInstances;

	for (int32 SplineCount = 0; SplineCount < NumberOfInstances; SplineCount++)
	{
		FRotator CurrentRotation = SplineComponent->GetRotationAtSplinePoint(SplineCount, ESplineCoordinateSpace::World);
		FVector UpVector = UKismetMathLibrary::GetUpVector(CurrentRotation);
		SplineComponent->SetUpVectorAtSplinePoint(SplineCount, UpVector, ESplineCoordinateSpace::World);

		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		SplineMeshComponent->SetStaticMesh(Mesh);
		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		SplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplineMeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
		SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SplineMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

		float StartDistance = (SplineCount) * (Spacing * StretchSize);
		float EndDistance = (SplineCount + 1) * (Spacing * StretchSize);
		float MidDistance = (StartDistance + EndDistance) / 2;

		FRotator MidRotation = SplineComponent->GetRotationAtDistanceAlongSpline(MidDistance, ESplineCoordinateSpace::Local);
		FVector MidUpVector = UKismetMathLibrary::GetUpVector(MidRotation);
		SplineMeshComponent->SetSplineUpDir(MidUpVector);

		FVector StartLocation = SplineComponent->GetLocationAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
		FVector EndLocation = SplineComponent->GetLocationAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
		FVector StartTangent = SplineComponent->GetTangentAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
		FVector ClampStartTangent = UKismetMathLibrary::ClampVectorSize(StartTangent, 0, Spacing);
		ClampStartTangent.Normalize(0.0001);
		FVector EndTangent = SplineComponent->GetTangentAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
		FVector ClampEndTangent = UKismetMathLibrary::ClampVectorSize(EndTangent, 0, Spacing);
		ClampEndTangent.Normalize(0.0001);
		FVector ArriveTangent = ClampStartTangent * Spacing;
		FVector LeaveTangent = ClampEndTangent * Spacing;
		SplineMeshComponent->SetStartAndEnd(StartLocation, ArriveTangent, EndLocation, LeaveTangent);

		FVector StartDirection = SplineComponent->GetDirectionAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
		FVector UnrotateStartDirection = UKismetMathLibrary::LessLess_VectorRotator(StartDirection, MidRotation);
		FVector StartRightVector = SplineComponent->GetRightVectorAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
		FVector UnrotateStartRight = UKismetMathLibrary::LessLess_VectorRotator(StartRightVector, MidRotation);
		FVector StartUpVector = SplineComponent->GetUpVectorAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
		FVector UnrotateStartUp = UKismetMathLibrary::LessLess_VectorRotator(StartUpVector, MidRotation);
		FRotator StartCombinedVector = UKismetMathLibrary::MakeRotationFromAxes(UnrotateStartDirection, UnrotateStartRight, UnrotateStartUp);

		FVector EndDirection = SplineComponent->GetDirectionAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
		FVector UnrotateEndDirection = UKismetMathLibrary::LessLess_VectorRotator(EndDirection, MidRotation);
		FVector EndRightVector = SplineComponent->GetRightVectorAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
		FVector UnrotateEndRight = UKismetMathLibrary::LessLess_VectorRotator(EndRightVector, MidRotation);
		FVector EndUpVector = SplineComponent->GetUpVectorAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
		FVector UnrotateEndUp = UKismetMathLibrary::LessLess_VectorRotator(EndUpVector, MidRotation);
		FRotator EndCombinedVector = UKismetMathLibrary::MakeRotationFromAxes(UnrotateEndDirection, UnrotateEndRight, UnrotateEndUp);

		SplineMeshComponent->SetStartRoll(FMath::DegreesToRadians(StartCombinedVector.Roll));
		SplineMeshComponent->SetEndRoll(FMath::DegreesToRadians(EndCombinedVector.Roll));

		FVector2D StartScale = UKismetMathLibrary::MakeVector2D(SplineComponent->GetScaleAtDistanceAlongSpline(StartDistance).X, SplineComponent->GetScaleAtDistanceAlongSpline(StartDistance).Y);
		FVector2D EndScale = UKismetMathLibrary::MakeVector2D(SplineComponent->GetScaleAtDistanceAlongSpline(EndDistance).X, SplineComponent->GetScaleAtDistanceAlongSpline(EndDistance).Y);
		SplineMeshComponent->SetStartScale(StartScale);
		SplineMeshComponent->SetEndScale(EndScale);
		if (AddSplineTrackToArray)
		{
			SplineMeshArray.Add(SplineMeshComponent);
		}
	}
	RegisterAllComponents();

	InsideSplineComponent->ClearSplinePoints();
	OutsideSplineComponent->ClearSplinePoints();
}