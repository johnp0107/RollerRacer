// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckForPlayerOnTrack.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UCheckForPlayerOnTrack::UCheckForPlayerOnTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCheckForPlayerOnTrack::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCheckForPlayerOnTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SphereTraceToFloor();
}

void UCheckForPlayerOnTrack::SphereTraceToFloor()
{
	AActor* Owner = GetOwner();
	const FVector Start = Owner->GetActorLocation();
	const FVector End = Owner->GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);
	TArray<FHitResult> HitArray;

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
		Start,
		End,
		75,
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

	UStaticMeshComponent* Mesh = Owner->FindComponentByClass<UStaticMeshComponent>();
	const FTransform WorldTransform = Mesh->GetComponentTransform();
	FBoxSphereBounds SphereBounds = Mesh->CalcBounds(WorldTransform);
	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{

			if (HitResult.GetActor()->GetName().Contains("Floor"))
			{
				//Center = HitResult.GetComponent()->GetLocalBounds() +  SphereBounds.SphereRadius;
				PlayerOnFloor = true;
			}
		}
	}
	else
	{
		FTimerHandle OverTheEdgeTimer;
		GetWorld()->GetTimerManager().SetTimer(
			OverTheEdgeTimer,
			this,
			&UCheckForPlayerOnTrack::PlacePlayerBackOnFloor,
			0.5f,
			false);
	}

}

void UCheckForPlayerOnTrack::PlacePlayerBackOnFloor()
{
	AActor* Owner = GetOwner();
	PlayerOnFloor = false;
	UStaticMeshComponent* Mesh = Owner->FindComponentByClass<UStaticMeshComponent>();
	Mesh->SetWorldLocation(Center);
}