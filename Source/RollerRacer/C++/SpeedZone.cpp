// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedZone.h"
#include "Components/BoxComponent.h"
#include "AIRollerRacerPawn.h"
#include "RollerRacerPawn.h"
#include "GameFramework/Actor.h"

ASpeedZone::ASpeedZone()
{
	PrimaryActorTick.bCanEverTick = true;
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpeedZone::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASpeedZone::OnOverlapEnd);

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);
}

void ASpeedZone::BeginPlay()
{
	Super::BeginPlay();
}

void ASpeedZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpeedZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        if (OtherActor->IsA(ARollerRacerPawn::StaticClass()))
        {
            ARollerRacerPawn* ActorAInstance = Cast<ARollerRacerPawn>(OtherActor);
            ActorAInstance->MaxSpeed = 3000;
        }
        else if (OtherActor->IsA(AAIRollerRacerPawn::StaticClass()))
        {
            AAIRollerRacerPawn* ActorAInstance = Cast<AAIRollerRacerPawn>(OtherActor);
            ActorAInstance->MaxSpeed = 3000;
        }
    }
}

void ASpeedZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this))
    {
        if (OtherActor->IsA(ARollerRacerPawn::StaticClass()))
        {
            ARollerRacerPawn* ActorAInstance = Cast<ARollerRacerPawn>(OtherActor);
            ActorAInstance->OutOfSpeedZoneTimer();
        }
        else if (OtherActor->IsA(AAIRollerRacerPawn::StaticClass()))
        {
            AAIRollerRacerPawn* ActorAInstance = Cast<AAIRollerRacerPawn>(OtherActor);
            ActorAInstance->OutOfSpeedZoneTimer();
        }
    }
}


