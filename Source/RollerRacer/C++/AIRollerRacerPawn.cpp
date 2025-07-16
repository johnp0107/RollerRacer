// Fill out your copyright notice in the Description page of Project Settings.


#include "AIRollerRacerPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AAIRollerRacerPawn::AAIRollerRacerPawn()
{
	AIMesh = CreateDefaultSubobject<UStaticMeshComponent>("AIMesh");
	AIMesh->SetSimulatePhysics(true);
	AIMesh->SetEnableGravity(false);
	SetRootComponent(AIMesh);

	AISpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	AISpringArm->SetupAttachment(AIMesh);
	AISpringArm->TargetArmLength = 500.0f;
	AISpringArm->SocketOffset.Z = 150;
	AISpringArm->bInheritPitch = false;
	AISpringArm->bInheritYaw = false;
	AISpringArm->bInheritRoll = false;
	AISpringArm->bDoCollisionTest = false;
	AISpringArm->bEnableCameraRotationLag = false;

	LevelSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Level"));
	LevelSceneComponent->SetupAttachment(AISpringArm, USpringArmComponent::SocketName);

	CaptureTexture = CreateDefaultSubobject<UCaptureTextureSnapshot>(TEXT("MyCustomComponent"));
	
	RacingComponent = CreateDefaultSubobject<URacingComponent>(TEXT("RacingComponent"));
	RacingComponent->CurrentLapNumber = 0;
	RacingComponent->ForwardCheckPointCounter = 4;
	RacingComponent->BackwardCheckPointCounter = 3;
	RacingComponent->MoveForce = 0;
	SplineCount = 0;
	NextPointDistance = 0;
	SplineTrackSelector = 0;

	MaxSpeed = 2000;
}

void AAIRollerRacerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (StaticMeshs.Num() > 0)
	{
		const int32 RandomMeshIndex = FMath::RandRange(0, StaticMeshs.Num() - 1);
		UStaticMesh* SelectedMesh = StaticMeshs[RandomMeshIndex];
		AIMesh->SetStaticMesh(SelectedMesh);

		if (Materials.Num() > 0)
		{
			const int32 RandomMaterialIndex = FMath::RandRange(0, Materials.Num() - 1);
			AIMesh->SetMaterial(0, Materials[RandomMaterialIndex]);
		}
	}

	AActor* SplineActorFound = UGameplayStatics::GetActorOfClass(GetWorld(), ASplineTrack::StaticClass());
	SplineActor = Cast<ASplineTrack>(SplineActorFound);

	RacerGameMode = Cast<ARollerRacerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (SplineActor)
	{
		SplinePointArray.Reset();
		SplinePointArray.Add(SplineActor->SplineComponent);
		SplinePointArray.Add(SplineActor->OutsideSplineComponent);
		SplinePointArray.Add(SplineActor->InsideSplineComponent);
	}

	RacingComponent->PassInfoFromParent(AIMesh, SplineActor ? SplineActor->SplineComponent : nullptr,
		LevelSceneComponent, this, AISpringArm);
	RacingComponent->CheckActorAboveFloor();

	CurrentSplineCount = 0;

	FVector StartLocation = AIMesh->GetComponentLocation();

	float Distance = RacingComponent->GetDistance(StartLocation);

	static FString SphereKeyword = TEXT("Sphere");
	static FString CylinderKeyword = TEXT("Cylinder");
	const FString MeshName = AIMesh->GetStaticMesh() ? AIMesh->GetStaticMesh()->GetFullName() : FString();

	if (MeshName.Contains(SphereKeyword))
	{
		const FTransform WorldTransform = AIMesh->GetComponentTransform();
		const FBoxSphereBounds SphereBounds = AIMesh->CalcBounds(WorldTransform);
		const float RadiusValue = SphereBounds.SphereRadius;

		if (SplinePointArray.Num() > 0)
		{
			const FVector ResetPosition = SplinePointArray[0]->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			const FVector UpVector = SplinePointArray[0]->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			const FVector AdjustedLocation = ResetPosition + UpVector * RadiusValue;

			StartLocation.Z = AdjustedLocation.Z;
		}
	}
	else if (MeshName.Contains(CylinderKeyword))
	{
		if (AIMesh->GetStaticMesh())
		{
			const FBoxSphereBounds MeshBounds = AIMesh->GetStaticMesh()->GetBounds();
			const float RadiusValue = FMath::Max(MeshBounds.BoxExtent.X, MeshBounds.BoxExtent.Y);

			if (SplinePointArray.Num() > 0)
			{
				const FVector ResetPosition = SplinePointArray[0]->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
				const FVector UpVector = SplinePointArray[0]->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
				const FVector AdjustedLocation = ResetPosition + UpVector * RadiusValue;

				StartLocation.Z = AdjustedLocation.Z;
			}
		}
	}

	AIMesh->SetWorldLocation(StartLocation);
	AIMesh->SetMobility(EComponentMobility::Static);

	if (SplinePointArray.IsValidIndex(SplineTrackSelector))
	{
		NextPointDistance = SplinePointArray[SplineTrackSelector]->GetDistanceAlongSplineAtSplinePoint(SplineCount);
	}
}

// Called every frame
void AAIRollerRacerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!AIMesh || AIMesh->Mobility == EComponentMobility::Static)
	{
		// Early out to avoid further processing if mobility isn't static
		return;
	}
		if (!RacingComponent->CheckActorOnFloor)
		{
			return; 
		}

		TurnToSplinePoint(DeltaTime);
		const float Distance = RacingComponent->GetDistance(AIMesh->GetComponentLocation());
		RacingComponent->CheckActorAboveFloor();
		RacingComponent->SetForwardAndDownVelocity(Distance, SplineActor ? SplineActor->SplineComponent : nullptr, AISpringArm, AIMesh);
		RacingComponent->TrackPlayerProgress(Distance);

		if (RacerGameMode && !RacerGameMode->ActorTextures.Contains(AITexture) && NumLapsCompleted <= RacerGameMode->MaxLapCount)
		{
			AITexture = CaptureTexture->ConvertStaticMeshToTexture2D(this, AIMesh, LevelSceneComponent);
			if (AITexture)
			{
				AITexture->Rename(*this->GetName(), AITexture->GetOuter());
				RacerGameMode->ActorTextures.Add(AITexture);
			}
		}

		TotalDistanceTravelled = RacingComponent->TotalDistanceTravelled;

		NumLapsCompleted = FMath::Max(1, RacingComponent->CurrentLapNumber);
}

void AAIRollerRacerPawn::TurnToSplinePoint(float DeltaTime)
{
	if (!SplinePointArray.IsValidIndex(CurrentSplineCount) || !SplinePointArray.IsValidIndex(SplineTrackSelector))
	{
		return; 
	}

	const USplineComponent* CurrentSpline = SplinePointArray[CurrentSplineCount];
	const USplineComponent* SelectedSpline = SplinePointArray[SplineTrackSelector];

	if (!CurrentSpline || !SelectedSpline)
	{
		return;
	}

	const float InputKey = CurrentSpline->FindInputKeyClosestToWorldLocation(AIMesh->GetComponentLocation());
	float Distance = CurrentSpline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	const float TotalDistance = SelectedSpline->GetSplineLength();

	if (Distance >= NextPointDistance && Distance <= NextPointDistance + 100)
	{
		const int32 PointCount = SelectedSpline->GetNumberOfSplinePoints();
		SplineCount = (SplineCount >= PointCount) ? 1 : (SplineCount + 1);
		SplineTrackSelector = FMath::RandRange(0, SplinePointArray.Num() - 1);
		NextPointDistance = SplinePointArray[SplineTrackSelector]->GetDistanceAlongSplineAtSplinePoint(SplineCount);
		CurrentSplineCount = SplineTrackSelector;
	}

	if (Distance > TotalDistance)
	{
		Distance -= TotalDistance;
	}

	const FVector NewTarget = SelectedSpline->GetLocationAtDistanceAlongSpline(Distance + 1000.0f, ESplineCoordinateSpace::World);
	SplineLocation = FMath::VInterpTo(SplineLocation, NewTarget, DeltaTime, 10.0f);

	const FTransform LevelForwardTransform = LevelSceneComponent->GetComponentTransform();
	const FVector LevelInverse = LevelForwardTransform.InverseTransformPosition(SplineLocation);
	const FRotator RotationToSplinePoint = UKismetMathLibrary::MakeRotFromX(LevelInverse);
	const float AngleToSplinePoint = RotationToSplinePoint.Yaw;

	if (AngleToSplinePoint < -5.0f)
	{
		Steering(-1.f);
		if (AngleToSplinePoint >= -10.f)
		{
			Accelerate(1.f);
		}
		else if (AngleToSplinePoint >= -20.f)
		{
			if (RacingComponent->MoveForce > 1000.f)
			{
				SlowDown();
			}
			else
			{
				Accelerate(1.f);
			}
		}
		else if (AngleToSplinePoint >= -30.f)
		{
			if (RacingComponent->MoveForce > 750.f)
			{
				Accelerate(-1.f);
			}
			else
			{
				Accelerate(1.f);
			}
		}
		else
		{
			if (RacingComponent->MoveForce > 500.f)
			{
				Accelerate(-1.f);
			}
			else
			{
				Accelerate(1.f);
			}
		}
	}
	else if (AngleToSplinePoint > 5.0f)
	{
		Steering(1.f);
		if (AngleToSplinePoint <= 10.f)
		{
			Accelerate(1.f);
		}
		else if (AngleToSplinePoint <= 20.f)
		{
			if (RacingComponent->MoveForce > 1000.f)
			{
				SlowDown();
			}
			else
			{
				Accelerate(1.f);
			}
		}
		else if (AngleToSplinePoint <= 30.f)
		{
			if (RacingComponent->MoveForce > 750.f)
			{
				Accelerate(-1.f);
			}
			else
			{
				Accelerate(1.f);
			}
		}
		else
		{
			if (RacingComponent->MoveForce > 500.f)
			{
				Accelerate(-1.f);
			}
			else
			{
				Accelerate(1.f);
			}
		}
	}
	else
	{
		Accelerate(1.f);
	}
}

void AAIRollerRacerPawn::Steering(float TurnValue)
{
	AISpringArm->AddLocalRotation(FRotator(0.f, TurnValue, 0.f));
}

void AAIRollerRacerPawn::Accelerate(float AccelerationDirectionValue)
{
	const float AccelerationValue = (AccelerationDirectionValue > 0) ? 10.f : 15.f;

	if (RacingComponent->MoveForce < MaxSpeed && RacingComponent->MoveForce > -500.f)
	{
		RacingComponent->MoveForce += AccelerationDirectionValue * AccelerationValue;
		RacingComponent->SlowDown = false;
	}
	else if (RacingComponent->MoveForce > MaxSpeed + 10.f)
	{
		RacingComponent->SlowDown = true;
	}
}

void AAIRollerRacerPawn::SlowDown()
{
	if (RacingComponent->MoveForce > 0.f)
	{
		RacingComponent->MoveForce -= 5.f;
	}
}

void AAIRollerRacerPawn::OutOfSpeedZoneTimer()
{
	if (!GetWorldTimerManager().IsTimerActive(OutOfSpeedZoneTimerHandle))
	{
		GetWorldTimerManager().SetTimer(
			OutOfSpeedZoneTimerHandle,
			this,
			&AAIRollerRacerPawn::ResetMaxSpeed,
			2.0f,
			false);
	}
}

void AAIRollerRacerPawn::ResetMaxSpeed()
{
	MaxSpeed = 2000;
}