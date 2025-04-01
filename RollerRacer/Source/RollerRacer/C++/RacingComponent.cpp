// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"


void URacingComponent::CheckActorAboveFloor()
{
	FHitResult HitResult;
	bool Hit = LineTraceToTrack(HitResult, 500);
	if (Hit)
	{

		if (HitResult.GetActor()->GetName().Contains("RaceTrack"))
		{
			GetWorld()->GetTimerManager().ClearTimer(OverTheEdgeTimerHandle);

			//GetWorldTimerManager().ClearTimer(OverTheEdgeTimerHandle);
			CheckActorOnFloor = true;
		}
	}
	if (!Hit && CheckActorOnFloor == true)
	{
		CheckActorOnFloor = false;
		ActorLocation = OwnerMesh->GetComponentLocation();
		GetWorld()->GetTimerManager().SetTimer(
			OverTheEdgeTimerHandle,
			this,
			&URacingComponent::AdvanceTimer,
			1.0f,
			false);
	}
}

void URacingComponent::AdvanceTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(OverTheEdgeTimerHandle);
	PlaceActorBackOnFloor(GetDistance(ActorLocation));
}

void URacingComponent::PlaceActorBackOnFloor(float Distance)
{
	MoveForce = 0;
	OwnerMesh->SetPhysicsLinearVelocity(FVector(0, 0, 0));
	FTransform WorldTransform = OwnerMesh->GetComponentTransform();
	FBoxSphereBounds SphereBounds = OwnerMesh->CalcBounds(WorldTransform);

	FVector ResetPosition = OwnerSplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector UpVector = OwnerSplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector Direction = UpVector * SphereBounds.SphereRadius;
	FVector AdjustedLocation = ResetPosition + Direction;
	UpVector.Normalize();

	FVector CurrentForward = UKismetMathLibrary::GetForwardVector(OwnerSpringArm->GetRelativeRotation());
	CurrentForward.Normalize();
	float ForwardDotProduct = FVector::DotProduct(CurrentForward, UpVector);
	float ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(ForwardDotProduct));
	FVector CameraLocationOnGround = OwnerSplineComponent->GetLocationAtDistanceAlongSpline(Distance + 200, ESplineCoordinateSpace::World);
	FVector WantedDirection = (CameraLocationOnGround - ResetPosition);
	WantedDirection.Normalize();
	float WantedDotProduct = FVector::DotProduct(WantedDirection, UpVector);
	float WantedAngle = FMath::RadiansToDegrees(FMath::Acos(WantedDotProduct));
	float PitchDifference = ForwardAngle - WantedAngle;
	OwnerSpringArm->AddLocalRotation(FRotator(PitchDifference, 0, 0));

	FVector LookAtLocation = OwnerSplineComponent->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	const FVector SpringArmLocation = OwnerSpringArm->GetComponentLocation();
	const FRotator NewYawRotation = FRotator(OwnerSpringArm->GetRelativeRotation().Pitch, LookAtLocation.Rotation().Yaw, OwnerSpringArm->GetRelativeRotation().Roll);
	OwnerSpringArm->SetRelativeRotation(NewYawRotation);

	OwnerActor->SetActorTransform(FTransform(NewYawRotation, AdjustedLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);
	OwnerMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	OwnerMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

	CheckActorOnFloor = true;
}

bool URacingComponent::LineTraceToTrack(FHitResult& HitResult, int32 LengthOfTrace)
{
	const FVector Start = OwnerMesh->GetComponentLocation();
	FVector DownVector = -OwnerSceneComponent->GetUpVector();


	const FVector End = DownVector * LengthOfTrace + Start;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	bool Hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);
	return Hit;
}

float URacingComponent::GetDistance(FVector Location)
{
	float InputKey = OwnerSplineComponent->FindInputKeyClosestToWorldLocation(Location);
	float Distance = OwnerSplineComponent->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	return Distance;
}

void URacingComponent::SetForwardAndDownVelocity(float Distance, USplineComponent* SplineComponent, USpringArmComponent* SpringArm, UStaticMeshComponent* Mesh)
{
	// Adjust SpringArm Pitch
	FVector MeshPositionOnSpline = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector UpVector = SplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	UpVector.Normalize();

	FVector CurrentForward = UKismetMathLibrary::GetForwardVector(SpringArm->GetRelativeRotation());
	CurrentForward.Normalize();
	float ForwardDotProduct = FVector::DotProduct(CurrentForward, UpVector);
	float ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(ForwardDotProduct));

	FVector CameraLocationOnGround = SplineComponent->GetLocationAtDistanceAlongSpline(Distance + 300, ESplineCoordinateSpace::World);
	FVector WantedDirection = (CameraLocationOnGround - MeshPositionOnSpline);
	WantedDirection.Normalize();
	float WantedDotProduct = FVector::DotProduct(WantedDirection, UpVector);
	float WantedAngle = FMath::RadiansToDegrees(FMath::Acos(WantedDotProduct));
	float PitchDifference = ForwardAngle - WantedAngle;
	SpringArm->AddLocalRotation(FRotator(PitchDifference, 0, 0));

	// Adjust SpringArm Roll
	FRotator CurrentRotation = SpringArm->GetRelativeRotation();
	FRotator NewSpringRotation = FRotationMatrix::MakeFromZX(UpVector, CurrentRotation.Vector()).Rotator();
	SpringArm->SetRelativeRotation(NewSpringRotation);

	if (MoveForce >= 0)
	{
		FVector BehindSpringArm = -(CurrentForward * 500) + (Mesh->GetComponentLocation());
		ForwardMovement = UKismetMathLibrary::FindLookAtRotation(BehindSpringArm, Mesh->GetComponentLocation()).Vector();
	}
	else if (MoveForce < 0)
	{
		FVector InfrontOfSpringArm = (CurrentForward * 500) + Mesh->GetComponentLocation();
		ForwardMovement = UKismetMathLibrary::FindLookAtRotation(Mesh->GetComponentLocation(), InfrontOfSpringArm).Vector();
	}
	FTransform WorldTransform = Mesh->GetComponentTransform();
	FBoxSphereBounds SphereBounds = Mesh->CalcBounds(WorldTransform);

	FHitResult HitResult;
	bool Hit = LineTraceToTrack(HitResult, SphereBounds.SphereRadius + 1);

	if (SlowDown && MoveForce > 0)
	{
		MoveForce -= 5;
	}
	if (SlowDown && MoveForce < 0)
	{
		MoveForce += 5;
	}
	if (Hit)
	{
		Gravity = FVector(0, 0, 0);
	}
	else
	{
		Gravity = -SplineComponent->GetUpVectorAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World) * 500;
	}
	FVector Forward = ForwardMovement * MoveForce;
	Mesh->SetPhysicsLinearVelocity(Forward);
	FVector CurrentVelocity = Mesh->GetComponentVelocity();
	FVector NewVelocity = CurrentVelocity + Gravity;
	Mesh->SetPhysicsLinearVelocity(NewVelocity);
}

void URacingComponent::PassInfoFromParent(UStaticMeshComponent* Mesh, USplineComponent* SplineComponent, USceneComponent* SceneComponent, AActor* Actor, USpringArmComponent* SpringArm)
{
	OwnerMesh = Mesh;

	OwnerSplineComponent = SplineComponent;

	OwnerActor = Actor;

	OwnerSceneComponent = SceneComponent;

	OwnerSpringArm = SpringArm;
}

void URacingComponent::TrackPlayerProgress(float Distance)
{
	float TotalDistance = OwnerSplineComponent->GetSplineLength() - 5;
	TArray<float> CheckPointDistance;

	for (int32 i = 0; i <= 4; i++)
	{
		CheckPointDistance.Add((0.25 * (TotalDistance)) * i);
	}

	FVector SplineDirection = OwnerSplineComponent->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector PlayerVelocity = OwnerActor->GetVelocity();
	IsMovingForward = FVector::DotProduct(SplineDirection, PlayerVelocity) >= 0;

	if (ForwardCheckPointCounter < 4)
	{
		NextCheckPointDistance = CheckPointDistance[ForwardCheckPointCounter];
	}
	else
	{
		NextCheckPointDistance = CheckPointDistance[0];
	}
	if (BackwardCheckPointCounter > 0)
	{
		PreviousCheckPointCounter = CheckPointDistance[ForwardCheckPointCounter];
	}
	else
	{
		PreviousCheckPointCounter = CheckPointDistance[4];
	}
	if (IsMovingForward)
	{
		if (Distance >= NextCheckPointDistance && Distance <= NextCheckPointDistance + 100)
		{
			if (ForwardCheckPointCounter == 4)
			{
				NumLapsCompleted++;
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
			if (BackwardCheckPointCounter == 0)
			{
				NumLapsCompleted--;
				BackwardCheckPointCounter = 3;
				ForwardCheckPointCounter = 4;
			}
			else
			{
				ForwardCheckPointCounter--;
				BackwardCheckPointCounter--;
			}
		}
	}
	TotalDistanceTravelled = Distance + (NumLapsCompleted * TotalDistance);
}