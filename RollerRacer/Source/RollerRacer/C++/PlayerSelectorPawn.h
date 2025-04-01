// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CaptureTextureSnapshot.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameStartWidget.h"
#include "RollerRacerGameInstance.h"
#include "PlayerSelectorPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateSelectorPawn, Log, All);

UCLASS()
class ROLLERRACER_API APlayerSelectorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerSelectorPawn();

	/** Ball mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh1;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh3;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*> Meshs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UMaterial*> RacerMaterials;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UTexture2D*> LevelImages;

	UPROPERTY()
	int32 CurrentMeshCount;

	/*UPROPERTY()
	int32 Mesh2Count;
	
	UPROPERTY()
	int32 Mesh3Count;*/

	UPROPERTY()
	int32 CurrentTrackCount;

	UPROPERTY()
	int32 AIPlayerCount;

	//UPROPERTY()
	//TArray<FString> RacerSelectorTextList;

	/*UPROPERTY()
	FString TextSelector;*/

	UPROPERTY()
	int32 TextCount;

	UPROPERTY()
	int32 MaterialCount;

	UPROPERTY()
	bool MoviePlaying = true;

	/*UPROPERTY()
	int32 Material2Count;*/

	/*UPROPERTY()
	int32 Material3Count;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
	TSubclassOf<class UGameStartWidget> WidgetClass;

	UPROPERTY()
	UGameStartWidget* MainMenuWidgetInstance;

	UPROPERTY()
	UCaptureTextureSnapshot* CaptureTexture;

	UPROPERTY()
	URollerRacerGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LeftRightSelectorAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UpDownSelectorAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* StartAction;

	UPROPERTY()
	UTexture2D* PlayerTexture;

	UPROPERTY()
	int32 MaxAIPlayerValue;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LeftRightSelector(const FInputActionValue& Value);

	void UpDownSelector(const FInputActionValue& Value);

	void Start(const FInputActionValue& Value);

};
