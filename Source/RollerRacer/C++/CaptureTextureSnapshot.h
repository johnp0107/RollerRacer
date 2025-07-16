// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/PointLightComponent.h"
#include "CaptureTextureSnapshot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLERRACER_API UCaptureTextureSnapshot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCaptureTextureSnapshot();
	
	UTexture2D* ConvertStaticMeshToTexture2D(AActor* Actor, UStaticMeshComponent* Mesh, USceneComponent* LevelSceneComponent);
		
};
