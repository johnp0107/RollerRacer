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
	FVector Forward = ForwardMovement * MoveForce;

	Mesh->SetPhysicsLinearVelocity(Forward);
	
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

	float RotSpeed = 0.5f; 
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
		}
	}
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

