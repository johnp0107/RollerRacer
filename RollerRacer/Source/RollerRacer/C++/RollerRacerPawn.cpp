// Fill out your copyright notice in the Description page of Project Settings.

#include "RollerRacerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "SphereTrace.h"
#include "TimerManager.h"
#include "CheckForPlayerOnTrack.h"

ARollerRacerPawn::ARollerRacerPawn()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	
	// Create the SpringArm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->TargetArmLength = 500.0f; 
	SpringArm->SocketOffset.Z = 200;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = false; 
	SpringArm->bEnableCameraLag = false; 
	SpringArm->CameraLagSpeed = 0;

	// Create the Camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SphereTrace = CreateDefaultSubobject<USphereTrace>(TEXT("SphereTrace"));
	SphereTrace->SetupAttachment(Mesh);

	CheckForPlayerOnTrack = CreateDefaultSubobject<UCheckForPlayerOnTrack>(TEXT("CheckForPlayerOnTrack"));
	CheckForPlayerOnTrack->SetupAttachment(Mesh);
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

// Called when the game starts or when spawned
void ARollerRacerPawn::BeginPlay()
{
	Super::BeginPlay();
	float TargetPitch = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), Mesh->GetComponentLocation()).Pitch;
	Camera->SetWorldRotation(FRotator(TargetPitch, Camera->GetComponentRotation().Yaw, Camera->GetComponentRotation().Roll));
}

// Called every frame
void ARollerRacerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AdjustCameraHeight();
	AdjustCameraRoll();
	if (MoveForce > 0)
	{
		ForwardMovement = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), Mesh->GetComponentLocation()).Vector();
	}
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
	double FloatValue = Value.Get<float>() * 2;
	//SpringArm->AddLocalRotation(FRotator(0, FloatValue, 0));

	FQuat CurrentRotation = SpringArm->GetRelativeRotation().Quaternion();
	float YawAdjustmentRadians = FMath::DegreesToRadians(FloatValue);
	FQuat YawRotation(FVector::UpVector, YawAdjustmentRadians);
	FQuat NewRotation = YawRotation * CurrentRotation;
	SpringArm->SetRelativeRotation(FRotator(SpringArm->GetRelativeRotation().Pitch , NewRotation.Rotator().Yaw, SpringArm->GetRelativeRotation().Roll));
}

void ARollerRacerPawn::AdjustCameraHeight()
{
	const FVector Start = Camera->GetComponentLocation();
	FVector DownVector = -Camera->GetUpVector();
	const FVector End = ((DownVector * 1000.f) + Start);
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

	const FTransform WorldTransform = Mesh->GetComponentTransform();
	FBoxSphereBounds SphereBounds = Mesh->CalcBounds(WorldTransform);
	
	if (Hit)
	{
		if (HitResult.GetActor()->GetName().Contains("Floor"))
		{

			if (MoveForce < 0)
			{
				ForwardMovement = UKismetMathLibrary::FindLookAtRotation(HitResult.ImpactPoint, Mesh->GetComponentLocation()).Vector();
			}

			FVector Direction = SpringArm->GetComponentLocation() - HitResult.ImpactPoint;
			Direction.Normalize();
			FQuat SpringRotation = FQuat::Slerp(SpringArm->GetRelativeRotation().Quaternion(), Direction.Rotation().Quaternion(), 1.0f);
			SpringArm->SetRelativeRotation(FRotator(SpringRotation.Rotator().Pitch, SpringArm->GetRelativeRotation().Yaw, SpringArm->GetRelativeRotation().Roll));
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
	DrawDebugLine(
		GetWorld(),
		Start,
		Right,
		FColor(255, 0, 0),
		false, -1, 0,
		12.333
	);

	bool HitLeft = GetWorld()->LineTraceSingleByChannel(
		HitLeftResult,
		Start,
		Left,
		ECC_Visibility,
		CollisionParams
	);
	DrawDebugLine(
		GetWorld(),
		Start,
		Left,
		FColor(255, 0, 0),
		false, -1, 0,
		12.333
	);

	if (HitRight && !HitLeft)
	{
		if (HitRightResult.GetActor()->GetName().Contains("Floor"))
		{
			Camera->AddLocalRotation(FRotator(0, 0, -2));
		}
	}
	else if (HitLeft && !HitRight)
	{
		if (HitLeftResult.GetActor()->GetName().Contains("Floor"))
		{
			Camera->AddLocalRotation(FRotator(0, 0, 2));
		}
	}
	
}

