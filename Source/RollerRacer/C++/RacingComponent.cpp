// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

constexpr int32 DefaultTraceLength = 500;
constexpr int32 CameraAheadDistance = 200;
constexpr int32 CameraAheadDistanceExtended = 300;
constexpr float SlowDownStep = 5.0f;
constexpr float GravityForce = 500.0f;
constexpr float ResetAdjustmentRadiusOffset = 1.0f;

void URacingComponent::CheckActorAboveFloor()
{
	FHitResult HitResult;
	const bool bHit = LineTraceToTrack(HitResult, DefaultTraceLength);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->GetName().Contains(TEXT("RaceTrack")))
		{
			if (GetWorld())
			{
				GetWorld()->GetTimerManager().ClearTimer(OverTheEdgeTimerHandle);
			}
			CheckActorOnFloor = true;
			return; 
		}
	}

	if (!bHit && CheckActorOnFloor)
	{
		CheckActorOnFloor = false;
		ActorLocation = OwnerMesh->GetComponentLocation();
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(
				OverTheEdgeTimerHandle,
				this,
				&URacingComponent::AdvanceTimer,
				1.0f,
				false);
		}
	}
}

void URacingComponent::AdvanceTimer()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(OverTheEdgeTimerHandle);
	}
	PlaceActorBackOnFloor(GetDistance(ActorLocation));
}

void URacingComponent::PlaceActorBackOnFloor(float Distance)
{
	MoveForce = 0;
	OwnerMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

	const FString MeshName = OwnerMesh->GetStaticMesh()->GetName();

	float Radius = 0.0f;
	if (MeshName.Contains(TEXT("Sphere")))
	{
		const FBoxSphereBounds SphereBounds = OwnerMesh->CalcBounds(OwnerMesh->GetComponentTransform());
		Radius = SphereBounds.SphereRadius - ResetAdjustmentRadiusOffset;
	}
	else if (MeshName.Contains(TEXT("Cylinder")))
	{
		const FBoxSphereBounds MeshBounds = OwnerMesh->GetStaticMesh()->GetBounds();
		Radius = FMath::Max(MeshBounds.BoxExtent.X, MeshBounds.BoxExtent.Y);
	}
	RadiusValue = Radius;

	const FVector ResetPosition = OwnerSplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector UpVector = OwnerSplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	const FVector Direction = UpVector * Radius;
	const FVector AdjustedLocation = ResetPosition + Direction;

	UpVector.Normalize();

	FVector CurrentForward = UKismetMathLibrary::GetForwardVector(OwnerSpringArm->GetRelativeRotation());
	CurrentForward.Normalize();

	const float ForwardDotProduct = FVector::DotProduct(CurrentForward, UpVector);
	const float ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(FMath::Clamp(ForwardDotProduct, -1.0f, 1.0f)));

	const FVector CameraLocationOnGround = OwnerSplineComponent->GetLocationAtDistanceAlongSpline(Distance + CameraAheadDistance, ESplineCoordinateSpace::World);
	FVector WantedDirection = CameraLocationOnGround - ResetPosition;
	WantedDirection.Normalize();

	const float WantedDotProduct = FVector::DotProduct(WantedDirection, UpVector);
	const float WantedAngle = FMath::RadiansToDegrees(FMath::Acos(FMath::Clamp(WantedDotProduct, -1.0f, 1.0f)));

	const float PitchDifference = ForwardAngle - WantedAngle;
	OwnerSpringArm->AddLocalRotation(FRotator(PitchDifference, 0, 0));

	const FVector LookAtLocation = OwnerSplineComponent->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	const FRotator CurrentSpringArmRot = OwnerSpringArm->GetRelativeRotation();
	const FRotator NewYawRotation = FRotator(CurrentSpringArmRot.Pitch, LookAtLocation.Rotation().Yaw, CurrentSpringArmRot.Roll);
	OwnerSpringArm->SetRelativeRotation(NewYawRotation);

	const FTransform NewTransform(NewYawRotation, AdjustedLocation, FVector::OneVector);

	OwnerActor->SetActorTransform(NewTransform, false, nullptr, ETeleportType::TeleportPhysics);

	OwnerMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	OwnerMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

	CheckActorOnFloor = true;
}

bool URacingComponent::LineTraceToTrack(FHitResult& HitResult, int32 LengthOfTrace)
{
	if (!OwnerMesh || !OwnerSceneComponent || !GetWorld())
	{
		return false;
	}

	const FVector Start = OwnerMesh->GetComponentLocation();
	const FVector DownVector = -OwnerSceneComponent->GetUpVector();
	const FVector End = Start + (DownVector * LengthOfTrace);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams);
}

float URacingComponent::GetDistance(FVector Location)
{
	if (!OwnerSplineComponent)
	{
		return 0.0f;
	}

	float InputKey = OwnerSplineComponent->FindInputKeyClosestToWorldLocation(Location);
	float Distance = OwnerSplineComponent->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	return Distance;
}

void URacingComponent::SetForwardAndDownVelocity(float Distance, USplineComponent* SplineComponent, USpringArmComponent* SpringArm, UStaticMeshComponent* Mesh)
{
	if (!SplineComponent || !SpringArm || !Mesh)
	{
		return;
	}

	const FVector MeshPositionOnSpline = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector UpVector = SplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	UpVector.Normalize();

	FVector CurrentForward = UKismetMathLibrary::GetForwardVector(SpringArm->GetRelativeRotation());
	CurrentForward.Normalize();

	float ForwardDotProduct = FVector::DotProduct(CurrentForward, UpVector);
	ForwardDotProduct = FMath::Clamp(ForwardDotProduct, -1.0f, 1.0f);

	const float ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(ForwardDotProduct));

	const FVector CameraLocationOnGround = SplineComponent->GetLocationAtDistanceAlongSpline(Distance + CameraAheadDistanceExtended, ESplineCoordinateSpace::World);
	FVector WantedDirection = CameraLocationOnGround - MeshPositionOnSpline;
	WantedDirection.Normalize();

	float WantedDotProduct = FVector::DotProduct(WantedDirection, UpVector);
	WantedDotProduct = FMath::Clamp(WantedDotProduct, -1.0f, 1.0f);

	const float WantedAngle = FMath::RadiansToDegrees(FMath::Acos(WantedDotProduct));

	const float PitchDifference = ForwardAngle - WantedAngle;
	SpringArm->AddLocalRotation(FRotator(PitchDifference, 0, 0));

	FRotator CurrentRotation = SpringArm->GetRelativeRotation();

	FRotator NewSpringRotation = FRotationMatrix::MakeFromZX(UpVector, CurrentRotation.Vector()).Rotator();
	SpringArm->SetRelativeRotation(NewSpringRotation);

	const FString MeshName = Mesh->GetStaticMesh() ? Mesh->GetStaticMesh()->GetName() : TEXT("");

	float Radius = 0.0f;
	if (MeshName.Contains(TEXT("Sphere")))
	{
		const FBoxSphereBounds SphereBounds = Mesh->CalcBounds(Mesh->GetComponentTransform());
		Radius = SphereBounds.SphereRadius - ResetAdjustmentRadiusOffset;
	}
	else if (MeshName.Contains(TEXT("Cylinder")))
	{
		const FBoxSphereBounds MeshBounds = Mesh->GetStaticMesh()->GetBounds();
		Radius = FMath::Max(MeshBounds.BoxExtent.X, MeshBounds.BoxExtent.Y);
	}
	RadiusValue = Radius;

	if (MoveForce >= 0.0f)
	{
		FVector BehindSpringArm = (Mesh->GetComponentLocation()) - (CurrentForward * 500.0f);
		ForwardMovement = UKismetMathLibrary::FindLookAtRotation(BehindSpringArm, Mesh->GetComponentLocation()).Vector();
	}
	else 
	{
		FVector InfrontOfSpringArm = (Mesh->GetComponentLocation()) + (CurrentForward * 500.0f);
		ForwardMovement = UKismetMathLibrary::FindLookAtRotation(Mesh->GetComponentLocation(), InfrontOfSpringArm).Vector();
	}

	FHitResult HitResult;
	const bool bHit = LineTraceToTrack(HitResult, FMath::RoundToInt(Radius));

	if (SlowDown)
	{
		if (MoveForce > 0)
		{
			MoveForce = FMath::Max(MoveForce - SlowDownStep, 0.0f);
		}
		else if (MoveForce < 0)
		{
			MoveForce = FMath::Min(MoveForce + SlowDownStep, 0.0f);
		}
	}

	if (bHit)
	{
		Gravity = FVector::ZeroVector;
	}
	else
	{
		Gravity = -SplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World) * GravityForce;
	}

	const FVector ForwardVelocity = ForwardMovement * MoveForce;

	FVector NewVelocity = ForwardVelocity + Gravity;
	Mesh->SetPhysicsLinearVelocity(NewVelocity);
}

void URacingComponent::PassInfoFromParent(UStaticMeshComponent* Mesh, USplineComponent* SplineComponent, USceneComponent* SceneComponent, AActor* Actor, USpringArmComponent* SpringArm)
{
	if (!Mesh || !SplineComponent || !SceneComponent || !Actor || !SpringArm)
	{
		return;
	}

	OwnerMesh = Mesh;
	OwnerSplineComponent = SplineComponent;
	OwnerActor = Actor;
	OwnerSceneComponent = SceneComponent;
	OwnerSpringArm = SpringArm;
}

void URacingComponent::TrackPlayerProgress(float Distance)
{
	if (!OwnerSplineComponent || !OwnerActor)
	{
		return;
	}

	float TotalDistance = OwnerSplineComponent->GetSplineLength() - 5;
	TArray<float> CheckPointDistances;
	static const int32 NumCheckpoints = 5;

	if (CheckPointDistances.Num() != NumCheckpoints)
	{
		CheckPointDistances.SetNum(NumCheckpoints);
	}

	for (int32 i = 0; i < NumCheckpoints; i++)
	{
		CheckPointDistances[i] = (i * 0.25f * TotalDistance);
	}

	FVector SplineDirection = OwnerSplineComponent->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector PlayerVelocity = OwnerActor->GetVelocity();
	
	IsMovingForward = FVector::DotProduct(SplineDirection, PlayerVelocity) >= 0;

	ForwardCheckPointCounter = FMath::Clamp(ForwardCheckPointCounter, 0, NumCheckpoints - 1);
	BackwardCheckPointCounter = FMath::Clamp(BackwardCheckPointCounter, 0, NumCheckpoints - 1);

	if (ForwardCheckPointCounter < 4)
	{
		NextCheckPointDistance = CheckPointDistances[ForwardCheckPointCounter];
	}
	else
	{
		NextCheckPointDistance = CheckPointDistances[0];
	}
	if (BackwardCheckPointCounter > 0)
	{
		PreviousCheckPointCounter = CheckPointDistances[ForwardCheckPointCounter];
	}
	else
	{
		PreviousCheckPointCounter = CheckPointDistances[4];
	}
	if (IsMovingForward)
	{
		if (Distance >= NextCheckPointDistance && Distance <= NextCheckPointDistance + 100)
		{
			if (ForwardCheckPointCounter == 4 || ForwardCheckPointCounter == 0)
			{
				CurrentLapNumber++;
				ForwardCheckPointCounter = 1;
				BackwardCheckPointCounter = 0;
			}
			else
			{
				ForwardCheckPointCounter++;
				BackwardCheckPointCounter++;
			}
		}
	}
	else
	{
		if (Distance <= PreviousCheckPointCounter && Distance >= PreviousCheckPointCounter - 100)
		{
			if (BackwardCheckPointCounter == 0 || BackwardCheckPointCounter == 4)
			{
				CurrentLapNumber--;
				BackwardCheckPointCounter = 3;
				ForwardCheckPointCounter = 0;
			}
			else
			{
				ForwardCheckPointCounter--;
				BackwardCheckPointCounter--;
			}
		}
	}
	TotalDistanceTravelled = Distance + (CurrentLapNumber * TotalDistance);
}