// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerRacerPlayerController.h"
#include "RollerRacerPawn.h"
#include "EnhancedInputSubsystems.h"

void ARollerRacerPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ARollerRacerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ARollerRacerPlayerController::Tick(float Delta)
{
	Super::Tick(Delta);
}

void ARollerRacerPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// get a pointer to the controlled pawn
	VehiclePawn = CastChecked<ARollerRacerPawn>(InPawn);
}