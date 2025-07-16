// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "RollerRacerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROLLERRACER_API URollerRacerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Settings")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Settings")
	UMaterial* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Settings")
	int32 AIRacerNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Settings")
	int32 NumberOfLaps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race Settings")
	int32 PlayerRacerNumber = 1;
};
