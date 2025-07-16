// Fill out your copyright notice in the Description page of Project Settings.

#include "RollerRacerGameMode.h"
#include "AIRollerRacerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "RollerRacerPawn.h"
#include "SpawnLocation.h"

void ARollerRacerGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<URollerRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	TArray<AActor*> SpawnLocationActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnLocation::StaticClass(), SpawnLocationActor);
	for (AActor* SpawnActor : SpawnLocationActor)
	{
		FVector ActorLocation = SpawnActor->GetActorLocation();
		SpawnLocations.Add(ActorLocation);

	}
	for (int32 i = 0; i < GameInstance->PlayerRacerNumber; i++)
	{
		int32 Index = FMath::RandRange(0, SpawnLocations.Num() - 1);
		FVector Start = SpawnLocations[Index];
		SpawnLocations.RemoveAt(Index);

		FRotator SpawnRotation = FRotator::ZeroRotator;
		ARollerRacerPawn* SpawnedPawn = GetWorld()->SpawnActor<ARollerRacerPawn>(PlayerBlueprint, Start, SpawnRotation);
		GetWorld()->GetFirstPlayerController()->Possess(SpawnedPawn);
		
	}
	for (int32 i = 0; i < GameInstance->AIRacerNumber; i++)
	{
		int32 Index = FMath::RandRange(0, SpawnLocations.Num() - 1);
		FVector Start = SpawnLocations[Index];
		SpawnLocations.RemoveAt(Index);

		FRotator SpawnRotation = FRotator::ZeroRotator;
		AAIRollerRacerPawn* SpawnedPawn = GetWorld()->SpawnActor<AAIRollerRacerPawn>(AIBlueprint, Start, SpawnRotation);	
	}

	MaxLapCount = GameInstance->NumberOfLaps;
	
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerRacerPawn::StaticClass(), PlayerActors);
	TArray<AActor*> AIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIRollerRacerPawn::StaticClass(), AIActors);
	if (AIActors.Num() > 0)
	{
		FoundActors.Append(AIActors);
	}
	if (PlayerActors.Num() > 0)
	{
		FoundActors.Append(PlayerActors);
	}


	GetWorldTimerManager().SetTimer(
		StartRaceTimerHandle,
		this,
		&ARollerRacerGameMode::StartRace,
		4.0f,
		false);
}

void ARollerRacerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OrderByDistance(FoundActors, FoundActors);
	float RemainingTime = FMath::RoundToInt(GetWorldTimerManager().GetTimerRemaining(StartRaceTimerHandle));
	if (RemainingTime > 0 && RemainingTime < 4)
	{
		StartTimerText = FString::SanitizeFloat(RemainingTime);
	}
	else if (RemainingTime == 0)
	{
		StartRace();
		GetWorldTimerManager().ClearTimer(StartRaceTimerHandle);
	}

	for (int32 i = 0; i < FoundActors.Num(); i++)
	{
		if (FoundActors[i]->IsA(ARollerRacerPawn::StaticClass()))
		{
			ARollerRacerPawn* ActorAInstance = Cast<ARollerRacerPawn>(FoundActors[i]);
			if (ActorAInstance->NumLapsCompleted > MaxLapCount && !RacerFinishedRaceList.Contains(FoundActors[i]))
			{
				RacerFinishedRaceList.Add(FoundActors[i]);
			}
		}
		else if (FoundActors[i]->IsA(AAIRollerRacerPawn::StaticClass()))
		{
			AAIRollerRacerPawn* ActorAInstance = Cast<AAIRollerRacerPawn>(FoundActors[i]);
			if (ActorAInstance->NumLapsCompleted > MaxLapCount && !RacerFinishedRaceList.Contains(FoundActors[i]))
			{
				RacerFinishedRaceList.Add(FoundActors[i]);
			}
		}
	}
		/*if (!RacerFinishedRaceList.IsEmpty())
	{
		for (int32 FinishedRacerNum = 0; FinishedRacerNum < RacerFinishedRaceList.Num(); FinishedRacerNum++)
		{
		for (int32 TextureNum = 0; TextureNum < ActorTextures.Num() - 1; TextureNum++)
			{
				if (FoundActors[FinishedRacerNum]->GetName() == ActorTextures[TextureNum]->GetName())
				{
					ActorTextures[FinishedRacerNum] = ActorTextures[TextureNum];
				}
			}

		}
	}*/
}

void ARollerRacerGameMode::StartRace()
{
	StartTimerText = "GO!";
	if (FoundActors.Num() > 0)
	{
		for (AActor* Actor : FoundActors)
		{
			UStaticMeshComponent* Mesh = Actor->FindComponentByClass<UStaticMeshComponent>();
			Mesh->SetMobility(EComponentMobility::Movable);
		}
	}
	GetWorldTimerManager().ClearTimer(StartRaceTimerHandle);
}

void ARollerRacerGameMode::OrderByDistance(TArray<AActor*> InArray, TArray<AActor*>& OutArray)
{
	InArray.Sort([](const AActor& A, const AActor& B)
		{
			float DistanceA = 0.0f;
			float DistanceB = 0.0f;

			if (const ARollerRacerPawn* PlayerRollerRacerA = Cast<ARollerRacerPawn>(&A))
			{
				DistanceA = PlayerRollerRacerA->TotalDistanceTravelled;
			}
			else if (const AAIRollerRacerPawn* AIRollerRacerA = Cast<AAIRollerRacerPawn>(&A))
			{
				DistanceA = AIRollerRacerA->TotalDistanceTravelled;
			}
			if (const ARollerRacerPawn* PlayerRollerRacerB = Cast<ARollerRacerPawn>(&B))
			{
				DistanceB = PlayerRollerRacerB->TotalDistanceTravelled;
			}
			else if (const AAIRollerRacerPawn* AIRollerRacerB = Cast<AAIRollerRacerPawn>(&B))
			{
				DistanceB = AIRollerRacerB->TotalDistanceTravelled;
			}
			return DistanceA > DistanceB;
		});
	OutArray = InArray;
}

int32 ARollerRacerGameMode::GetActorPosition(AActor* GetPositionOfActor)
{
	int32 Position;
	for (int32 i = 0; i < FoundActors.Num(); i++)
	{
		if (FoundActors[i] == GetPositionOfActor)
		{
			Position = i + 1;
		}
	}
	return Position;
}

void ARollerRacerGameMode::PauseRace()
{
	if (FoundActors.Num() > 0)
	{
		for (AActor* Actor : FoundActors)
		{
			UStaticMeshComponent* Mesh = Actor->FindComponentByClass<UStaticMeshComponent>();
			Mesh->SetMobility(EComponentMobility::Static);
		}
	}
}

void ARollerRacerGameMode::UnPauseRace()
{
	if (FoundActors.Num() > 0)
	{
		for (AActor* Actor : FoundActors)
		{
			UStaticMeshComponent* Mesh = Actor->FindComponentByClass<UStaticMeshComponent>();
			Mesh->SetMobility(EComponentMobility::Movable);
		}
	}
}

