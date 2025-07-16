// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UInputMappingContext;
class APlayerSelectorPawn;
UCLASS()
class ROLLERRACER_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	/** Pointer to the controlled vehicle pawn */
	TObjectPtr<APlayerSelectorPawn> VehiclePawn;

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


protected:

	virtual void OnPossess(APawn* InPawn) override;
};
