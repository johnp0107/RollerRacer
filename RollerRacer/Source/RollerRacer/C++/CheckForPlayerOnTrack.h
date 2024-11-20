// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CheckForPlayerOnTrack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLERRACER_API UCheckForPlayerOnTrack : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCheckForPlayerOnTrack();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector Center;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SphereTraceToFloor();

	UFUNCTION()
	void PlacePlayerBackOnFloor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool PlayerOnFloor = true;
};
