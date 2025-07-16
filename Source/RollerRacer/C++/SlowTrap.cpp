// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowTrap.h"
#include "Components/BoxComponent.h"
#include "AIRollerRacerPawn.h"
#include "RollerRacerPawn.h"
#include "GameFramework/Actor.h"

// Sets default values
ASlowTrap::ASlowTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASlowTrap::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASlowTrap::OnOverlapEnd);

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASlowTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlowTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlowTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        if (OtherActor->IsA(ARollerRacerPawn::StaticClass()))
        {
            ARollerRacerPawn* ActorAInstance = Cast<ARollerRacerPawn>(OtherActor);
            ActorAInstance->MaxSpeed = 1500;
        }
        else if (OtherActor->IsA(AAIRollerRacerPawn::StaticClass()))
        {
            AAIRollerRacerPawn* ActorAInstance = Cast<AAIRollerRacerPawn>(OtherActor);
            ActorAInstance->MaxSpeed = 1500;
        }
    }
}

void ASlowTrap::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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


