// Fill out your copyright notice in the Description page of Project Settings.


#include "AIRollerRacerPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AAIRollerRacerPawn::AAIRollerRacerPawn()
{

	AIMesh = CreateDefaultSubobject<UStaticMeshComponent>("AIMesh");
	AIMesh->SetSimulatePhysics(true);
	AIMesh->SetEnableGravity(false);

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
	RacingComponent->NumLapsCompleted = -1;
	RacingComponent->ForwardCheckPointCounter = 4;
	RacingComponent->BackwardCheckPointCounter = 3;
	RacingComponent->MoveForce = 0;
	SplineCount = 0;
	NextPointDistance = 0;
	SplineTrackSelector = 0;
}

// Called when the game starts or when spawned
void AAIRollerRacerPawn::BeginPlay()
{
	AIMesh->SetMobility(EComponentMobility::Static);
	Super::BeginPlay();
	int32 RandomMeshCount = FMath::RandRange(0, StaticMeshs.Num() - 1);
	AIMesh->SetStaticMesh(StaticMeshs[RandomMeshCount]);
	int32 RandomMaterialCount = FMath::RandRange(0, Materials.Num() - 1);
	AIMesh->SetMaterial(0, Materials[RandomMaterialCount]);
	
	float TargetPitch = UKismetMathLibrary::FindLookAtRotation(LevelSceneComponent->GetComponentLocation(), AIMesh->GetComponentLocation()).Pitch;
	LevelSceneComponent->SetWorldRotation(FRotator(TargetPitch, LevelSceneComponent->GetComponentRotation().Yaw, LevelSceneComponent->GetComponentRotation().Roll));

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASplineTrack::StaticClass());
	SplineActor = Cast<ASplineTrack>(FoundActor);

	RacerGameMode = Cast<ARollerRacerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	FVector MeshLocation = AIMesh->GetComponentLocation();

	SplinePointArray.Add(SplineActor->SplineComponent);
	SplinePointArray.Add(SplineActor->OutsideSplineComponent);
	SplinePointArray.Add(SplineActor->InsideSplineComponent);
	RacingComponent->PassInfoFromParent(AIMesh, SplineActor->SplineComponent, LevelSceneComponent, this, AISpringArm);
}

// Called every frame
void AAIRollerRacerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AIMesh->Mobility)
	{
		if (RacingComponent->CheckActorOnFloor)
		{
			TurnToSplinePoint(DeltaTime);
		}
		float Distance = RacingComponent->GetDistance(AIMesh->GetComponentLocation());
		RacingComponent->CheckActorAboveFloor();
		RacingComponent->SetForwardAndDownVelocity(Distance, SplineActor->SplineComponent, AISpringArm, AIMesh);
		RacingComponent->TrackPlayerProgress(Distance);

		if (!RacerGameMode->ActorTextures.Contains(AITexture))
		{
			AITexture = CaptureTexture->ConvertStaticMeshToTexture2D(this, AIMesh, LevelSceneComponent);
			AITexture->Rename(*this->GetName(), AITexture->GetOuter());
			RacerGameMode->ActorTextures.Add(AITexture);
		}
		TotalDistanceTravelled = RacingComponent->TotalDistanceTravelled;
	}  
}

void AAIRollerRacerPawn::TurnToSplinePoint(float DeltaTime)
{
	float Distance = RacingComponent->GetDistance(AIMesh->GetComponentLocation());
	float TotalDistance = SplinePointArray[SplineTrackSelector]->GetSplineLength();

	if (Distance >= NextPointDistance)
	{
		if (SplineCount == SplinePointArray[0]->GetNumberOfSplinePoints())
		{
			SplineCount = 0;
		}
		else
		{
			SplineCount++;
		}
		SplineTrackSelector = FMath::RandRange(0, 2);
	}
	NextPointDistance = SplinePointArray[SplineTrackSelector]->GetDistanceAlongSplineAtSplinePoint(SplineCount);
	
	// Check if the point the AI is looking for it greater than the total length of the spling, and adjust if it is
	if (AheadDistance + 500 > TotalDistance)
	{
		AheadDistance -= TotalDistance;
	}
	else
	{
		AheadDistance = Distance + 500;
	}
	FVector NewTarget = SplinePointArray[SplineTrackSelector]->GetLocationAtDistanceAlongSpline(AheadDistance, ESplineCoordinateSpace::World);
	SplineLocation = FMath::VInterpTo(SplineLocation, NewTarget, DeltaTime, 10.0f);
	
	FTransform LevelForwardTransform = LevelSceneComponent->GetComponentTransform();
	FVector LevelInverse = LevelForwardTransform.InverseTransformPosition(SplineLocation);
	FRotator RotationToSplinePoint = UKismetMathLibrary::MakeRotFromX(LevelInverse);
	float AngleToSplinePoint = RotationToSplinePoint.Yaw;

	if (AngleToSplinePoint < 5 && AngleToSplinePoint >= -10)
	{
		Steering(-1);
		Accelerate(1);
	}
	else if (AngleToSplinePoint < -10 && AngleToSplinePoint >= -20)
	{
		Steering(-1);
		if (RacingComponent->MoveForce > 1000)
		{
			SlowDown();
		}
		else if (RacingComponent->MoveForce <= 1000)
		{
			Accelerate(1);
		}
	}
	else if (AngleToSplinePoint < -20 && AngleToSplinePoint >= -30)
	{
		Steering(-1);
		if (RacingComponent->MoveForce > 750)
		{
			Accelerate(-1);
		}
		else if (RacingComponent->MoveForce <= 750)
		{
			Accelerate(1);
		}
	}
	else if (AngleToSplinePoint < -30)
	{
		Steering(-1);
		if (RacingComponent->MoveForce > 500)
		{
			Accelerate(-1);
		}
		else if (RacingComponent->MoveForce <= 500)
		{
			Accelerate(1);
		}
	}
	else if (AngleToSplinePoint > 5 && AngleToSplinePoint <= 10)
	{
		Steering(1);
		Accelerate(1);
	}
	else if (AngleToSplinePoint > 10 && AngleToSplinePoint <= 20)
	{
		Steering(1);
		if (RacingComponent->MoveForce > 1000)
		{
			SlowDown();
		}
		else if (RacingComponent->MoveForce <= 1000)
		{
			Accelerate(1);
		}
	}
	else if (AngleToSplinePoint > 20 && AngleToSplinePoint <= 30)
	{
		Steering(1);
		if (RacingComponent->MoveForce > 750)
		{
			Accelerate(-1);
		}
		else if (RacingComponent->MoveForce <= 750)
		{
			Accelerate(1);
		}
	}
	else if (AngleToSplinePoint > 30)
	{
		Steering(1);
		if (RacingComponent->MoveForce > 500)
		{
			Accelerate(-1);
		}
		else if (RacingComponent->MoveForce <= 500)
		{
			Accelerate(1);
		}
	}
	else
	{
		Accelerate(1);
	}
}

void AAIRollerRacerPawn::Steering(float TurnValue)
{
	AISpringArm->AddLocalRotation(FRotator(0, TurnValue, 0));
}

void AAIRollerRacerPawn::Accelerate(float AccelerationDirectionValue)
{
	float AccelerationValue = 10;

	if (AccelerationDirectionValue > 0)
	{
		AccelerationValue = 10;
	}
	else
	{
		AccelerationValue = 15;
	}

	if (RacingComponent->MoveForce < 2000 && RacingComponent->MoveForce > -500)
	{
		RacingComponent->MoveForce += (AccelerationDirectionValue * AccelerationValue);
	}
}

void AAIRollerRacerPawn::SlowDown()
{
	if (RacingComponent->MoveForce > 0)
	{
		RacingComponent->MoveForce -= 5;
	}
}