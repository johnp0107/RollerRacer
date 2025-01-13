// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineTrack.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RollerRacerPawn.h"

// Sets default values
ASplineTrack::ASplineTrack()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	if (SplineComponent)
	{
		SetRootComponent(SplineComponent);
	}
}

// Called when the game starts or when spawned
void ASplineTrack::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASplineTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerRacerPawn::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		float Distance = SplineComponent->GetDistanceAlongSplineAtSplineInputKey(SplineComponent->FindInputKeyClosestToWorldLocation(Actor->GetActorLocation()));
		
	}
}

void ASplineTrack::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!Mesh)
	{
		return;
	}


	for (int32 SplineCount = 0; SplineCount < (SplineComponent->GetNumberOfSplinePoints() - 1); SplineCount++)
	{
		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		SplineMeshComponent->SetStaticMesh(Mesh);
		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		SplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		//SplineMeshComponent->RegisterComponentWithWorld(GetWorld());
		SplineMeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

		FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
		SplineComponent->GetLocalLocationAndTangentAtSplinePoint(SplineCount, pointLocationStart, pointTangentStart);
		SplineComponent->GetLocalLocationAndTangentAtSplinePoint(SplineCount + 1, pointLocationEnd, pointTangentEnd);
		SplineMeshComponent->SetStartAndEnd(pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd, true);

		SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SplineMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
		
		/*FRotator StartRoll = SplineComponent->GetRotationAtSplinePoint(SplineCount, ESplineCoordinateSpace::World);
		FRotator EndRoll = SplineComponent->GetRotationAtSplinePoint(SplineCount+1, ESplineCoordinateSpace::World);
		SplineMeshComponent->SetStartRollDegrees(StartRoll.Roll);
		SplineMeshComponent->SetEndRollDegrees(EndRoll.Roll);*/

		FVector SplineUp = SplineComponent->GetUpVectorAtSplinePoint(SplineCount, ESplineCoordinateSpace::World);
		SplineMeshComponent->SetSplineUpDir(SplineUp);


		
	}
	RegisterAllComponents();
}

