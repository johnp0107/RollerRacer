// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollerRacerGameModeBase.generated.h"


UCLASS()
class ROLLERRACER_API ARollerRacerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "PlayerPositionTracker")
	TArray<UTexture2D*> ActorTextures;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMesh* StaticMesh;

	UPROPERTY()
	UMaterial* Material;

	UPROPERTY()
	int32 AIRacerNumber;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float Delta) override;
	
	


};
