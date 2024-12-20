// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollerRacerPawn.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class USphereTrace;
class UCheckForPlayerOnTrack;
struct FInputActionValue;

UCLASS()
class ROLLERRACER_API ARollerRacerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollerRacerPawn();

	/** Ball mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereTrace* SphereTrace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCheckForPlayerOnTrack* CheckForPlayerOnTrack;

	/** Throttle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ThrottleAction;

	/** Steering Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SteeringAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ForwardMovement;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool SlowDown = false;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Throttle(const FInputActionValue& Value);

	UFUNCTION()
	void ReleaseThrottle(const FInputActionValue& Value);

	UFUNCTION()
	void Steering(const FInputActionValue& Value);

	UFUNCTION()
	void AdjustCameraHeight();

	UFUNCTION()
	void AdjustCameraRoll();

};
