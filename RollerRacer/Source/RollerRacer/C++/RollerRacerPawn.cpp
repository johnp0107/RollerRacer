// Fill out your copyright notice in the Description page of Project Settings.

#include "RollerRacerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

ARollerRacerPawn::ARollerRacerPawn()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);

	TargetComponent = CreateDefaultSubobject<USceneComponent>("Target");
	TargetComponent->SetupAttachment(Mesh);

	MeshLocationComponent = CreateDefaultSubobject<USceneComponent>("MeshLocation");
	MeshLocationComponent->SetupAttachment(Mesh);

	PivotSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PivotSpringArm"));
	PivotSpringArm->SetupAttachment(Mesh);
	PivotSpringArm->TargetArmLength = 400.0f;
	PivotSpringArm->SocketOffset.Z = 150;
	PivotSpringArm->bUseAttachParentBound = false;
	PivotSpringArm->bInheritPitch = false;
	PivotSpringArm->bInheritYaw = false;
	PivotSpringArm->bInheritRoll = false;
	PivotSpringArm->bDoCollisionTest = false;

	// Create the SpringArm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset.Z = 150;
	SpringArm->bUseAttachParentBound = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 5;

	// Create the Camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SphereTrace = CreateDefaultSubobject<USphereTrace>(TEXT("SphereTrace"));
	SphereTrace->SetupAttachment(RootComponent);

	CheckForPlayerOnTrack = CreateDefaultSubobject<UCheckForPlayerOnTrack>(TEXT("CheckForPlayerOnTrack"));
	CheckForPlayerOnTrack->SetupAttachment(RootComponent);
}

// Called to bind functionality to input
void ARollerRacerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::Steering);

		// throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ARollerRacerPawn::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ARollerRacerPawn::ReleaseThrottle);
	}
}

void ARollerRacerPawn::BeginPlay()
{
	Super::BeginPlay();
	MoveForce = 0;
	float TargetPitch = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), Mesh->GetComponentLocation()).Pitch;
	Camera->SetWorldRotation(FRotator(TargetPitch, Camera->GetComponentRotation().Yaw, Camera->GetComponentRotation().Roll));
}

void ARollerRacerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AdjustCameraHeight();
	AdjustCameraRoll();
	SetForwardMovement();
	/*if (MoveForce > 0)
	{
		FVector Midpoint = (Camera->GetComponentLocation() + HitPoint) / 2;
		ForwardMovement = UKismetMathLibrary::FindLookAtRotation(Midpoint, Mesh->GetComponentLocation()).Vector();
	}*/
	FVector Forward = ForwardMovement * MoveForce;

	Mesh->SetPhysicsLinearVelocity(Forward);
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, ForwardMovement.ToString());

	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "Look At: " + FString::SanitizeFloat(MoveForce));
	if (SlowDown && MoveForce > 0)
	{
		MoveForce -= 5;
	}
	if (SlowDown && MoveForce < 0)
	{
		MoveForce += 5;
	}
	if (CheckForPlayerOnTrack->PlayerOnFloor == false)
	{
		MoveForce = 0;
	}

	FQuat CurrentRotation = SpringArm->GetRelativeRotation().Quaternion();

	FQuat DesiredRotation = PivotSpringArm->GetRelativeRotation().Quaternion();

	float RotSpeed = 0.5f; // Adjust this for desired smoothness
	FQuat NewRotation = FQuat::Slerp(CurrentRotation, DesiredRotation, RotSpeed * DeltaTime);
	SpringArm->SetRelativeRotation(DesiredRotation);

}

void ARollerRacerPawn::Throttle(const FInputActionValue& Value)
{
	double FloatValue = Value.Get<float>();
	if (MoveForce < 2000 && MoveForce > -500)
	{
		MoveForce += FloatValue * 10;
	}
	SlowDown = false;
}

void ARollerRacerPawn::ReleaseThrottle(const FInputActionValue& Value)
{
	SlowDown = true;
}

void ARollerRacerPawn::Steering(const FInputActionValue& Value)
{
	double FloatValue = Value.Get<float>();
	SpringArm->AddLocalRotation(FRotator(0, FloatValue, 0));
	PivotSpringArm->AddLocalRotation(FRotator(0, FloatValue, 0));
}

void ARollerRacerPawn::AdjustCameraHeight()
{
	/*const FVector Start = SpringArm->GetComponentLocation();
	FVector ForwardVector = -UKismetMathLibrary::GetUpVector(SpringArm->GetRelativeRotation());
	const FVector End = ForwardVector * 1000.f + Start;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool Hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);


	const FVector Start2 = SpringArm->GetComponentLocation();
	FVector ForwardVector2 = Camera->GetForwardVector();
	const FVector End2 = ForwardVector2 * 1000.f + Start2;
	FHitResult HitResult2;

	bool Hit2 = GetWorld()->LineTraceSingleByChannel(
		HitResult2,
		Start2,
		End2,
		ECC_Visibility,
		CollisionParams
	);*/

	const FVector Start = Camera->GetComponentLocation();
	FVector ForwardVector = -Camera->GetUpVector();
	const FVector End = ForwardVector * 1000.f + Start;
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool Hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);



	///*DrawDebugLine(
	//	GetWorld(),
	//	Start,
	//	ForwardVector,
	//	FColor(255, 0, 0),
	//	false, -1, 0,
	//	1.333
	//);*/

	/*if (Hit2)
	{

		if (HitResult2.GetActor()->GetName().Contains("RaceTrack"))
		{
			TargetComponent->SetWorldLocation(HitResult2.ImpactPoint);
		}
	}*/

	if (Hit)
	{
		if (HitResult.GetActor()->GetName().Contains("RaceTrack"))
		{
			CameraHeight = (Camera->GetComponentLocation() - HitResult.ImpactPoint).Length();
			if (CameraHeight > 250)
			{
				PivotSpringArm->AddLocalRotation(FRotator(3, 0, 0));
			}
			else if (CameraHeight < MinCameraHeight)
			{
				PivotSpringArm->AddLocalRotation(FRotator(-3, 0, 0));
			}
			HitPoint = HitResult.ImpactPoint;

			if (MoveForce < 0)
			{
				ForwardMovement = UKismetMathLibrary::FindLookAtRotation(HitPoint, Mesh->GetComponentLocation()).Vector();
			}
			//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "HitResult: " + FString::SanitizeFloat(CameraHeight));
		}
	}

	/*const FTransform WorldTransform = Mesh->GetComponentTransform();
	FBoxSphereBounds SphereBounds = Mesh->CalcBounds(WorldTransform);*/
	//if (Hit)
	//{

	//	if (HitResult.GetActor()->GetName().Contains("RaceTrack"))
	//	{
	//		//MeshLocationComponent->SetWorldLocation(HitResult.ImpactPoint);
	//		
	//		/*FVector Direction = Mesh->GetComponentLocation() - Camera->GetComponentLocation();
	//		Direction.Y = 0;*/
	//		/*FRotator rotation = UKismetMathLibrary::FindLookAtRotation(HitResult.ImpactPoint, Mesh->GetComponentLocation());
	//		float DotProduct = FVector::DotProduct(UKismetMathLibrary::GetForwardVector(SpringArm->GetRelativeRotation()), HitResult.ImpactPoint);
	//		float AcosAngle = FMath::Acos(DotProduct);
	//		float AimAtAngle = FMath::RadiansToDegrees(AcosAngle);*/


	//		// Works for dot product but broken on X and Y
	//		/*FVector MeshForward = UKismetMathLibrary::GetForwardVector(SpringArm->GetRelativeRotation());
	//		MeshForward.Normalize();
	//		MeshForward.Y = 0;
	//		FVector HitForward = SpringArm->GetComponentLocation() - HitResult.ImpactPoint;
	//		HitForward.Normalize();
	//		HitForward.Y = 0;
	//		float dot = FVector::DotProduct(HitForward, MeshForward);
	//		float angle = FMath::Acos(dot);*/
	//		// End of Good
	//		// X = 0 and Y = 0 for both is 1.5 rad Dot = 0

	//		//FVector MeshLocation = SphereTrace->AdjustedLocation;
	//		///*MeshLocation.X = 0;
	//		//MeshLocation.Y = 0;*/
	//		//FVector HitLocation = TargetComponent->GetComponentLocation();
	//		/*HitLocation.X = 0;
	//		HitLocation.Y = 0;*/

	//		//FVector Direction = (TargetComponent->GetComponentLocation() - MeshLocationComponent->GetComponentLocation()).GetSafeNormal();

	//		////HitForward.Normalize();
	//		////
	//		//FVector MeshDirection = UKismetMathLibrary::GetForwardVector(SpringArm->GetRelativeRotation()).GetSafeNormal();
	//		////FQuat MeshForward = MeshDirection.ToOrientationQuat();
	//		//float MeshDot = FVector::DotProduct(FVector::UpVector, MeshDirection);
	//		//float DirectionDot = FVector::DotProduct(FVector::UpVector, Direction);
	//		////SpringArm->SetRelativeRotation(Direction.ToOrientationQuat());
	//		////MeshForward.Normalize();
	//		///*if (MeshDirection.Rotation().Roll == 180)
	//		//{
	//		//	PitchValue = -PitchValue;
	//		//}*/
	//		////FQuat Forward = MeshForward.Inverse() * Direction.ToOrientationQuat();
	//		//float MeshAngle = FMath::Acos(MeshDot);
	//		//float DirectionAngle = FMath::Acos(DirectionDot);
	//		////float angle = MeshAngle - DirectionAngle;
	//		//float angle = Direction.Rotation().Pitch - MeshDirection.Rotation().Pitch;


	//		/*FQuat CurrentQuat = SpringArm->GetRelativeRotation().Quaternion();
	//		FQuat Rotation = PitchDifference * MeshForward;
	//		SpringArm->SetRelativeRotation(Rotation);*/

	//		/*float Difference = HitResult.ImpactPoint.Z - (Mesh->GetComponentLocation().Z-50);*/
	//		/*float dot = FVector::DotProduct(Direction, MeshForward);
	//		float angle = FMath::Acos(dot);*/

	//		//FQuat CurrentQuat = MeshForward.ToOrientationQuat();
	//		//FQuat Rotation = PitchDifference * CurrentQuat;

	//		/*if (PitchDifference < 0)
	//		{
	//			PitchDifference = -PitchDifference;
	//		}*/
	//		//SpringArm->AddLocalRotation(FRotator(PitchDifference, 0, 0));
	//		//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "HitResult: " + FString::SanitizeFloat(angle));
	//		//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "Mesh: " + FString::SanitizeFloat(MeshForward.Rotator().Pitch - FVector::UpVector.Rotation().Pitch));

	//		/*GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "SpringArm: " + SpringArm->GetRelativeRotation().ToString());
	//		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, "PivotSpringArm: " + PivotSpringArm->GetRelativeRotation().ToString());*/

	//		/*FVector vec1 = HitResult.ImpactPoint.GetSafeNormal();
	//		FVector vec2 = Mesh->GetComponentLocation().GetSafeNormal();
	//		float Angle = 0.0f;
	//		FVector nAxis;

	//		FQuat BetweenQuat = FQuat::FindBetweenVectors(vec1, vec2);

	//		BetweenQuat.ToAxisAndAngle(nAxis, Angle);*/


	//		/*FQuat DirectionQuat = Direction.ToOrientationQuat();


	//		FRotator SpringArmRotation = SpringArm->GetRelativeRotation();
	//		FQuat SpringArmQuat = SpringArmRotation.Quaternion();
	//		float Pitch = DirectionQuat.Rotator().Pitch - SpringArmQuat.Rotator().Pitch;
	//		FQuat FinalRotation = DirectionQuat - SpringArmQuat;*/
	//		/*FQuat CurrentQuat = Camera->GetComponentQuat();
	//		FQuat Rotation = DirectionQuat * CurrentQuat;*/

	//		/*FRotator Final = FinalRotation.Rotator();*/
	//		//SpringArm->SetRelativeRotation(DesiredRotation);


	//		/*if (PitchValue < 0)
	//		{
	//			PitchValue = -PitchValue;
	//		}*/

	//		//FQuat PitchQuat = FQuat(UKismetMathLibrary::GetRightVector(SpringArm->GetRelativeRotation()) , -FMath::DegreesToRadians(angle));
	//		/*FQuat PitchQuat = PivotSpringArm->GetRelativeRotation().Quaternion();
	//		FQuat CurrentQuat = SpringArm->GetRelativeRotation().Quaternion();
	//		FQuat Rotation = FQuat::Slerp(CurrentQuat, PitchQuat, 0.5f);
	//		SpringArm->SetRelativeRotation(Rotation);*/

	//		/*FQuat Direction = MyLookRotation(Mesh->GetComponentLocation(), HitResult.ImpactPoint).Quaternion();
	//		FQuat CurrentQuat = SpringArm->GetRelativeRotation().Quaternion();
	//		FQuat Rotation = CurrentQuat * Direction;*/
	//		/*SpringArm->SetRelativeRotation(DesiredRotation);*/
	//		//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "Rotation: " + SpringArm->GetRelativeRotation().Quaternion().ToString());
	//		//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "CurrentQuat: " + CurrentQuat.ToString());

	//		//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, "Direction: " + FString::SanitizeFloat(angle ));

	//		if (MoveForce < 0)
	//		{
	//			ForwardMovement = UKismetMathLibrary::FindLookAtRotation(HitPoint, Mesh->GetComponentLocation()).Vector();
	//		}
	//	}
	//}
	/*else
	{
		if (MoveForce < 0)
		{
			FVector LookPoint = FVector(Camera->GetComponentLocation().X, Camera->GetComponentLocation().Y, HitPoint.Z);
			ForwardMovement = UKismetMathLibrary::FindLookAtRotation(LookPoint, Mesh->GetComponentLocation()).Vector();
		}
	}*/
}

void ARollerRacerPawn::AdjustCameraRoll()
{
	const FVector Start = Camera->GetComponentLocation();
	FVector RightVector = Camera->GetRightVector();
	FVector LeftVector = -Camera->GetRightVector();
	const FVector Right = ((RightVector * 1000.f) + Start);
	const FVector Left = ((LeftVector * 1000.f) + Start);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	FHitResult HitRightResult;
	FHitResult HitLeftResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool HitRight = GetWorld()->LineTraceSingleByChannel(
		HitRightResult,
		Start,
		Right,
		ECC_Visibility,
		CollisionParams
	);
	bool HitLeft = GetWorld()->LineTraceSingleByChannel(
		HitLeftResult,
		Start,
		Left,
		ECC_Visibility,
		CollisionParams
	);

	if (HitRight && !HitLeft)
	{
		if (HitRightResult.GetActor()->GetName().Contains("RaceTrack"))
		{
			PivotSpringArm->AddLocalRotation(FRotator(0, 0, -2));
		}
	}
	else if (HitLeft && !HitRight)
	{
		if (HitLeftResult.GetActor()->GetName().Contains("RaceTrack"))
		{
			PivotSpringArm->AddLocalRotation(FRotator(0, 0, 2));
		}
	}
}

void ARollerRacerPawn::SetForwardMovement()
{
	FVector Start = Camera->GetComponentLocation();
	FVector ForwardVector = Camera->GetForwardVector();
	FVector End = ForwardVector * 1000.f + Start;
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool Hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);

	if (Hit)
	{
		if (HitResult.GetActor()->GetName().Contains("RaceTrack"))
		{
			MinCameraHeight = 150;
				if (MoveForce > 0)
				{
					FVector Midpoint = (Camera->GetComponentLocation() + HitPoint) / 2;
					ForwardMovement = UKismetMathLibrary::FindLookAtRotation(Midpoint, Mesh->GetComponentLocation()).Vector();
				}
		}
		
	}
	else
		{
		MinCameraHeight = 240;
			if (MoveForce > 0)
			{
				ForwardMovement = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), Mesh->GetComponentLocation()).Vector();
			}
		}
}

