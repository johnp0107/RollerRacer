// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RollerRacerGameInstance.h"
#include "GameFramework/GameMode.h"
#include "RollerRacerGameMode.generated.h"


UCLASS()
class ROLLERRACER_API ARollerRacerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "PlayerPositionTracker")
	TArray<AActor*> FoundActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle StartRaceTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Spawn Locations")
	TArray<FVector> SpawnLocations;

	UPROPERTY()
	URollerRacerGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, Category = "AIPlayer")
	TSubclassOf<AActor> AIBlueprint;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<AActor> PlayerBlueprint;

	UPROPERTY(VisibleAnywhere, Category = "PlayerPositionTracker")
	TArray<UTexture2D*> ActorTextures;

	UPROPERTY(VisibleAnywhere, Category = "PlayerPositionTracker")
	int32 MaxLapCount;

	UPROPERTY(VisibleAnywhere, Category = "PlayerPositionTracker")
	TArray<AActor*> RacerFinishedRaceList;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	FString StartTimerText;

	void StartRace();

	void PauseRace();

	void UnPauseRace();

	int32 GetActorPosition(AActor* Actors);

	void OrderByDistance(TArray<AActor*> InArray, TArray<AActor*>& OutArray);
};
