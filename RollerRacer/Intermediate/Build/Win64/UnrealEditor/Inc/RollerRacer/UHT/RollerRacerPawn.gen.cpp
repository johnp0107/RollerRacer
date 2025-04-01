// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RollerRacer/C++/RollerRacerPawn.h"
#include "Runtime/Engine/Classes/Engine/TimerHandle.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRollerRacerPawn() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTimerHandle();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_ARollerRacerGameMode_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_ARollerRacerPawn();
ROLLERRACER_API UClass* Z_Construct_UClass_ARollerRacerPawn_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_ASplineTrack_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_UCaptureTextureSnapshot_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_URaceTrackingWidget_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_URacingComponent_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_URollerRacerGameInstance_NoRegister();
UPackage* Z_Construct_UPackage__Script_RollerRacer();
// End Cross Module References

// Begin Class ARollerRacerPawn
void ARollerRacerPawn::StaticRegisterNativesARollerRacerPawn()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARollerRacerPawn);
UClass* Z_Construct_UClass_ARollerRacerPawn_NoRegister()
{
	return ARollerRacerPawn::StaticClass();
}
struct Z_Construct_UClass_ARollerRacerPawn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "C++/RollerRacerPawn.h" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Ball mesh */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ball mesh" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringArm_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelSceneComponent_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThrottleAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Throttle Action */" },
#endif
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Throttle Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SteeringAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Steering Action */" },
#endif
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Steering Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorLocation_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplineComponent_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplineActor_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RacerGameMode_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThreeSecondTimerHandle_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayGoTimerHandle_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalDistanceTravelled_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorTextures_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WidgetClass_MetaData[] = {
		{ "Category", "MyActor" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RacePositionWidgetInstance_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CaptureTexture_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RacingComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MySoundWave_MetaData[] = {
		{ "Category", "Audio" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WrongWayWave_MetaData[] = {
		{ "Category", "Audio" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelAudio_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WrongWayAudio_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HideBackwardsDisplay_MetaData[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerTexture_MetaData[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GameInstance_MetaData[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LevelSceneComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ThrottleAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SteeringAction;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ActorLocation;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SplineComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SplineActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RacerGameMode;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ThreeSecondTimerHandle;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DisplayGoTimerHandle;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TotalDistanceTravelled;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Position;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorTextures_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActorTextures;
	static const UECodeGen_Private::FClassPropertyParams NewProp_WidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RacePositionWidgetInstance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CaptureTexture;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RacingComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MySoundWave;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WrongWayWave;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LevelAudio;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WrongWayAudio;
	static void NewProp_HideBackwardsDisplay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_HideBackwardsDisplay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerTexture;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GameInstance;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARollerRacerPawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringArm_MetaData), NewProp_SpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_LevelSceneComponent = { "LevelSceneComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, LevelSceneComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelSceneComponent_MetaData), NewProp_LevelSceneComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ThrottleAction = { "ThrottleAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, ThrottleAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThrottleAction_MetaData), NewProp_ThrottleAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SteeringAction = { "SteeringAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, SteeringAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SteeringAction_MetaData), NewProp_SteeringAction_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ActorLocation = { "ActorLocation", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, ActorLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorLocation_MetaData), NewProp_ActorLocation_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SplineComponent = { "SplineComponent", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, SplineComponent), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplineComponent_MetaData), NewProp_SplineComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SplineActor = { "SplineActor", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, SplineActor), Z_Construct_UClass_ASplineTrack_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplineActor_MetaData), NewProp_SplineActor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_RacerGameMode = { "RacerGameMode", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, RacerGameMode), Z_Construct_UClass_ARollerRacerGameMode_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RacerGameMode_MetaData), NewProp_RacerGameMode_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ThreeSecondTimerHandle = { "ThreeSecondTimerHandle", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, ThreeSecondTimerHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThreeSecondTimerHandle_MetaData), NewProp_ThreeSecondTimerHandle_MetaData) }; // 756291145
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_DisplayGoTimerHandle = { "DisplayGoTimerHandle", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, DisplayGoTimerHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayGoTimerHandle_MetaData), NewProp_DisplayGoTimerHandle_MetaData) }; // 756291145
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_TotalDistanceTravelled = { "TotalDistanceTravelled", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, TotalDistanceTravelled), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalDistanceTravelled_MetaData), NewProp_TotalDistanceTravelled_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, Position), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ActorTextures_Inner = { "ActorTextures", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ActorTextures = { "ActorTextures", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, ActorTextures), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorTextures_MetaData), NewProp_ActorTextures_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_WidgetClass = { "WidgetClass", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, WidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_URaceTrackingWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WidgetClass_MetaData), NewProp_WidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_RacePositionWidgetInstance = { "RacePositionWidgetInstance", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, RacePositionWidgetInstance), Z_Construct_UClass_URaceTrackingWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RacePositionWidgetInstance_MetaData), NewProp_RacePositionWidgetInstance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_CaptureTexture = { "CaptureTexture", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, CaptureTexture), Z_Construct_UClass_UCaptureTextureSnapshot_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CaptureTexture_MetaData), NewProp_CaptureTexture_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_RacingComponent = { "RacingComponent", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, RacingComponent), Z_Construct_UClass_URacingComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RacingComponent_MetaData), NewProp_RacingComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MySoundWave = { "MySoundWave", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, MySoundWave), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MySoundWave_MetaData), NewProp_MySoundWave_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_WrongWayWave = { "WrongWayWave", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, WrongWayWave), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WrongWayWave_MetaData), NewProp_WrongWayWave_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_LevelAudio = { "LevelAudio", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, LevelAudio), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelAudio_MetaData), NewProp_LevelAudio_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_WrongWayAudio = { "WrongWayAudio", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, WrongWayAudio), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WrongWayAudio_MetaData), NewProp_WrongWayAudio_MetaData) };
void Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_HideBackwardsDisplay_SetBit(void* Obj)
{
	((ARollerRacerPawn*)Obj)->HideBackwardsDisplay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_HideBackwardsDisplay = { "HideBackwardsDisplay", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ARollerRacerPawn), &Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_HideBackwardsDisplay_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HideBackwardsDisplay_MetaData), NewProp_HideBackwardsDisplay_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_PlayerTexture = { "PlayerTexture", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, PlayerTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerTexture_MetaData), NewProp_PlayerTexture_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_GameInstance = { "GameInstance", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, GameInstance), Z_Construct_UClass_URollerRacerGameInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GameInstance_MetaData), NewProp_GameInstance_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARollerRacerPawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_LevelSceneComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ThrottleAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SteeringAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ActorLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SplineComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SplineActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_RacerGameMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ThreeSecondTimerHandle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_DisplayGoTimerHandle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_TotalDistanceTravelled,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ActorTextures_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ActorTextures,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_WidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_RacePositionWidgetInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_CaptureTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_RacingComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MySoundWave,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_WrongWayWave,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_LevelAudio,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_WrongWayAudio,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_HideBackwardsDisplay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_PlayerTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_GameInstance,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPawn_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ARollerRacerPawn_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_RollerRacer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPawn_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ARollerRacerPawn_Statics::ClassParams = {
	&ARollerRacerPawn::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ARollerRacerPawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPawn_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPawn_Statics::Class_MetaDataParams), Z_Construct_UClass_ARollerRacerPawn_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ARollerRacerPawn()
{
	if (!Z_Registration_Info_UClass_ARollerRacerPawn.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARollerRacerPawn.OuterSingleton, Z_Construct_UClass_ARollerRacerPawn_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ARollerRacerPawn.OuterSingleton;
}
template<> ROLLERRACER_API UClass* StaticClass<ARollerRacerPawn>()
{
	return ARollerRacerPawn::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ARollerRacerPawn);
ARollerRacerPawn::~ARollerRacerPawn() {}
// End Class ARollerRacerPawn

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ARollerRacerPawn, ARollerRacerPawn::StaticClass, TEXT("ARollerRacerPawn"), &Z_Registration_Info_UClass_ARollerRacerPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARollerRacerPawn), 403091945U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_3646389855(TEXT("/Script/RollerRacer"),
	Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
