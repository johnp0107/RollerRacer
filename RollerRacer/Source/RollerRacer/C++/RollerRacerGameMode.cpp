// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerRacerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AIRollerRacerPawn.h"
#include "RollerRacerPawn.h"

void ARollerRacerGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<URollerRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
		/*if (SpawnLocations.Num() > 0)
		{*/
			TArray<AActor*> PlayerActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerRacerPawn::StaticClass(), PlayerActors);
			
			for (AActor* Actor : PlayerActors)
			{
				// Randomly select player location
				int32 Index = FMath::RandRange(0, SpawnLocations.Num() - 1);
				FVector Start = SpawnLocations[Index];

				// Remove the selected location to avoid overlap
				SpawnLocations.RemoveAt(Index);

				// Set Player location
				Actor->SetActorLocation(Start);

			}
			for (int32 i = 0; i < GameInstance->AIRacerNumber; i++)
			{
				int32 Index = FMath::RandRange(0, SpawnLocations.Num() - 1);
				FVector Start = SpawnLocations[Index];
				SpawnLocations.RemoveAt(Index);

				FRotator SpawnRotation = FRotator::ZeroRotator;
				AAIRollerRacerPawn* SpawnedPawn = GetWorld()->SpawnActor<AAIRollerRacerPawn>(AIBlueprint, Start, SpawnRotation);
			}
		//}


	//if (SpawnLocations.Num() > 0)
	//{
	//	for (AActor* Actor : FoundActors)
	//	{
	//		// Randomly select player location
	//		int32 Index = FMath::RandRange(0, SpawnLocations.Num() - 1);
	//		FVector Start = SpawnLocations[Index];

	//		// Remove the selected location to avoid overlap
	//		SpawnLocations.RemoveAt(Index);

	//		// Set Player location
	//		Actor->SetActorLocation(Start);

	//	}
	//}
	//TArray<AActor*> PlayerActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollerRacerPawn::StaticClass(), PlayerActors);
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
	int32 PlayerPosition{};
	for (int32 i = 0; i < FoundActors.Num(); i++)
	{
		if (FoundActors[i] == GetPositionOfActor)
		{
			PlayerPosition = i + 1;
		}
	}
	return PlayerPosition;
}
