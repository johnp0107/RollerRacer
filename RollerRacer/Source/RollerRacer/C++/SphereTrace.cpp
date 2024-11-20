// Fill out your copyright notice in the Description page of Project Settings.
#include "SphereTrace.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
USphereTrace::USphereTrace()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USphereTrace::BeginPlay()
{
	Super::BeginPlay();
	AdjustPlayerPosition();
}


// Called every frame
void USphereTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FVector USphereTrace::GetDirectionBetweenPoints(const FVector& PointA, const FVector& PointB)
{
	FVector Direction = PointB - PointA;
	Direction.Normalize();
	return Direction;
}

void USphereTrace::AdjustPlayerPosition()
{
	AActor* Owner = GetOwner();

	// Store the Start and End locations of the trace, as we are using the radius of the sphere, these can be the same,
	const FVector Start = Owner->GetActorLocation();
	const FVector End = Owner->GetActorLocation();
	// Array of Actors to ignore i.e NOT to trace against. 
	TArray<AActor*> ActorsToIgnore;
	// Add Actor this is attached on to be ignored.
	ActorsToIgnore.Add(Owner);
	// Variable to store the hit information returned from the trace.
	TArray<FHitResult> HitArray;

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
		Start,
		End,
		TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitArray,
		true,
		FLinearColor::Gray,
		FLinearColor::Blue,
		60.0f
	);

	UStaticMeshComponent* StaticMeshComp = Owner->FindComponentByClass<UStaticMeshComponent>();
	const FTransform MeshTransform = StaticMeshComp->GetComponentTransform();
	FBoxSphereBounds SphereSize = StaticMeshComp->CalcBounds(MeshTransform);
	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{
			if (HitResult.GetActor()->GetName().Contains("Floor"))
			{
				FVector direction = GetDirectionBetweenPoints(HitResult.ImpactPoint, Owner->GetActorLocation());
				FVector AdjustedLocation = HitResult.ImpactPoint + direction * SphereSize.SphereRadius;

				Owner->SetActorLocation(AdjustedLocation);
			}

		}
	}
}

