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
    if (!Actor || !Mesh || !LevelSceneComponent)
    {
        return nullptr;
    }

    const FBox ObjectBoundingBox = Actor->GetComponentsBoundingBox();
    const FVector BoxExtent = ObjectBoundingBox.GetExtent();
    const FVector ObjectCenter = ObjectBoundingBox.GetCenter();
    const FVector ViewLocation = LevelSceneComponent->GetComponentLocation();

    const float Distance = FVector::Dist(ViewLocation, ObjectCenter);

    USceneCaptureComponent2D* SceneCapture = NewObject<USceneCaptureComponent2D>(Actor);
    if (!SceneCapture)
    {
        return nullptr;
    }

    SceneCapture->RegisterComponentWithWorld(Actor->GetWorld());
    SceneCapture->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

    SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
    SceneCapture->ProjectionType = ECameraProjectionMode::Perspective;
    SceneCapture->FOVAngle = FMath::RadiansToDegrees(2.0f * FMath::Atan(BoxExtent.X / FMath::Max(Distance, 1.f))) + 2;
    SceneCapture->OrthoWidth = 0.f;

    SceneCapture->CompositeMode = ESceneCaptureCompositeMode::SCCM_Overwrite;
    SceneCapture->bCaptureOnMovement = false;
    SceneCapture->bCaptureEveryFrame = false;
    SceneCapture->ShowOnlyComponent(Mesh);

    constexpr int32 RenderTargetSize = 1024;
    UTextureRenderTarget2D* RenderTarget = NewObject<UTextureRenderTarget2D>(this);
    RenderTarget->RenderTargetFormat = RTF_RGBA8;
    RenderTarget->InitAutoFormat(RenderTargetSize, RenderTargetSize);
    RenderTarget->TargetGamma = 1.5f;
    RenderTarget->ClearColor = FLinearColor::Transparent;
    RenderTarget->UpdateResourceImmediate(true);

    SceneCapture->TextureTarget = RenderTarget;

    SceneCapture->SetWorldLocation(ViewLocation);
    SceneCapture->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(ViewLocation, Mesh->GetComponentLocation()));
    SceneCapture->CaptureScene();

    FTextureRenderTargetResource* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
    if (!RenderTargetResource)
    {
        return nullptr;
    }

    TArray<FColor> Bitmap;
    if (!RenderTargetResource->ReadPixels(Bitmap))
    {
        return nullptr;
    }

    UTexture2D* OutTexture =
        UTexture2D::CreateTransient(RenderTargetSize, RenderTargetSize, PF_B8G8R8A8);

    if (!OutTexture)
    {
        return nullptr;
    }

    OutTexture->SRGB = RenderTarget->SRGB;

    FTexture2DMipMap& Mip = OutTexture->GetPlatformData()->Mips[0];
    void* DataPtr = Mip.BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(DataPtr, Bitmap.GetData(), Bitmap.Num() * sizeof(FColor));
    Mip.BulkData.Unlock();

    OutTexture->UpdateResource();

    SceneCapture->DestroyComponent();

    return OutTexture;
}