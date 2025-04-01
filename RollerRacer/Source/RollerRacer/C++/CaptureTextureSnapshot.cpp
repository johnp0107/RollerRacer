// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureTextureSnapshot.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCaptureTextureSnapshot::UCaptureTextureSnapshot()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UTexture2D* UCaptureTextureSnapshot::ConvertStaticMeshToTexture2D(AActor* Actor, UStaticMeshComponent* Mesh, USceneComponent* LevelSceneComponent)
{
	USceneCaptureComponent2D* SceneCapture = NewObject<USceneCaptureComponent2D>(Mesh);
	SceneCapture->SetupAttachment(Mesh);
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	SceneCapture->ProjectionType = ECameraProjectionMode::Type::Perspective;
	
	FBox ObjectBoundingBox = Actor->GetComponentsBoundingBox();
	FVector BoxExtent = ObjectBoundingBox.GetExtent(); // Half-size dimensions
	FVector ObjectCenter = ObjectBoundingBox.GetCenter();
	float Distance = FVector::Dist(LevelSceneComponent->GetComponentLocation(), ObjectCenter);
	float OrthoWidth = FMath::Max(BoxExtent.X, BoxExtent.Y) * 2.0f;
	SceneCapture->OrthoWidth = OrthoWidth;
	float FOV = FMath::RadiansToDegrees(2.0f * FMath::Atan(BoxExtent.X / Distance));
	SceneCapture->FOVAngle = FOV + 2;

	SceneCapture->CompositeMode = ESceneCaptureCompositeMode::SCCM_Overwrite;
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->ShowOnlyComponent(Mesh);
	UTextureRenderTarget2D* RenderTarget = NewObject<UTextureRenderTarget2D>();
	RenderTarget->InitAutoFormat(1024, 1024);
	RenderTarget->TargetGamma = 1.5;
	RenderTarget->UpdateResourceImmediate(true);
	SceneCapture->TextureTarget = RenderTarget;
	SceneCapture->SetWorldLocation(LevelSceneComponent->GetComponentLocation());
	SceneCapture->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(LevelSceneComponent->GetComponentLocation(), Mesh->GetComponentLocation()));
	
	FTextureRenderTargetResource* RenderTargetResource = SceneCapture->TextureTarget->GameThread_GetRenderTargetResource();
	UTexture2D* OutTexture = UTexture2D::CreateTransient(SceneCapture->TextureTarget->SizeX, SceneCapture->TextureTarget->SizeY);
	OutTexture->SRGB = SceneCapture->TextureTarget->SRGB;
	SceneCapture->CaptureScene();
	TArray<FColor> Bitmap;
	RenderTargetResource->ReadPixels(Bitmap);

	void* TextureData = OutTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, Bitmap.GetData(), Bitmap.Num() * sizeof(FColor));
	OutTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

	OutTexture->UpdateResource();

	return OutTexture;
}


