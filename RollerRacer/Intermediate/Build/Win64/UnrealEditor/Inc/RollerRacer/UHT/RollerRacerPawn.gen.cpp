// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RollerRacer/C++/RollerRacerPawn.h"
#include "EnhancedInput/Public/InputActionValue.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRollerRacerPawn() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UScriptStruct* Z_Construct_UScriptStruct_FInputActionValue();
ROLLERRACER_API UClass* Z_Construct_UClass_ARollerRacerPawn();
ROLLERRACER_API UClass* Z_Construct_UClass_ARollerRacerPawn_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_UCheckForPlayerOnTrack_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_USphereTrace_NoRegister();
UPackage* Z_Construct_UPackage__Script_RollerRacer();
// End Cross Module References

// Begin Class ARollerRacerPawn Function AdjustCameraHeight
struct Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraHeight_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraHeight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARollerRacerPawn, nullptr, "AdjustCameraHeight", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraHeight_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraHeight_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraHeight()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraHeight_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARollerRacerPawn::execAdjustCameraHeight)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AdjustCameraHeight();
	P_NATIVE_END;
}
// End Class ARollerRacerPawn Function AdjustCameraHeight

// Begin Class ARollerRacerPawn Function AdjustCameraRoll
struct Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraRoll_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraRoll_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARollerRacerPawn, nullptr, "AdjustCameraRoll", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraRoll_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraRoll_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraRoll()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraRoll_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARollerRacerPawn::execAdjustCameraRoll)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AdjustCameraRoll();
	P_NATIVE_END;
}
// End Class ARollerRacerPawn Function AdjustCameraRoll

// Begin Class ARollerRacerPawn Function ReleaseThrottle
struct Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics
{
	struct RollerRacerPawn_eventReleaseThrottle_Parms
	{
		FInputActionValue Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RollerRacerPawn_eventReleaseThrottle_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) }; // 494646648
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARollerRacerPawn, nullptr, "ReleaseThrottle", nullptr, nullptr, Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::RollerRacerPawn_eventReleaseThrottle_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::RollerRacerPawn_eventReleaseThrottle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARollerRacerPawn::execReleaseThrottle)
{
	P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ReleaseThrottle(Z_Param_Out_Value);
	P_NATIVE_END;
}
// End Class ARollerRacerPawn Function ReleaseThrottle

// Begin Class ARollerRacerPawn Function SetForwardMovement
struct Z_Construct_UFunction_ARollerRacerPawn_SetForwardMovement_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARollerRacerPawn_SetForwardMovement_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARollerRacerPawn, nullptr, "SetForwardMovement", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_SetForwardMovement_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARollerRacerPawn_SetForwardMovement_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ARollerRacerPawn_SetForwardMovement()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARollerRacerPawn_SetForwardMovement_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARollerRacerPawn::execSetForwardMovement)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetForwardMovement();
	P_NATIVE_END;
}
// End Class ARollerRacerPawn Function SetForwardMovement

// Begin Class ARollerRacerPawn Function Steering
struct Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics
{
	struct RollerRacerPawn_eventSteering_Parms
	{
		FInputActionValue Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RollerRacerPawn_eventSteering_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) }; // 494646648
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARollerRacerPawn, nullptr, "Steering", nullptr, nullptr, Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::RollerRacerPawn_eventSteering_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::RollerRacerPawn_eventSteering_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARollerRacerPawn_Steering()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARollerRacerPawn_Steering_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARollerRacerPawn::execSteering)
{
	P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Steering(Z_Param_Out_Value);
	P_NATIVE_END;
}
// End Class ARollerRacerPawn Function Steering

// Begin Class ARollerRacerPawn Function Throttle
struct Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics
{
	struct RollerRacerPawn_eventThrottle_Parms
	{
		FInputActionValue Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RollerRacerPawn_eventThrottle_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) }; // 494646648
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARollerRacerPawn, nullptr, "Throttle", nullptr, nullptr, Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::RollerRacerPawn_eventThrottle_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::RollerRacerPawn_eventThrottle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARollerRacerPawn_Throttle()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARollerRacerPawn_Throttle_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARollerRacerPawn::execThrottle)
{
	P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Throttle(Z_Param_Out_Value);
	P_NATIVE_END;
}
// End Class ARollerRacerPawn Function Throttle

// Begin Class ARollerRacerPawn
void ARollerRacerPawn::StaticRegisterNativesARollerRacerPawn()
{
	UClass* Class = ARollerRacerPawn::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AdjustCameraHeight", &ARollerRacerPawn::execAdjustCameraHeight },
		{ "AdjustCameraRoll", &ARollerRacerPawn::execAdjustCameraRoll },
		{ "ReleaseThrottle", &ARollerRacerPawn::execReleaseThrottle },
		{ "SetForwardMovement", &ARollerRacerPawn::execSetForwardMovement },
		{ "Steering", &ARollerRacerPawn::execSteering },
		{ "Throttle", &ARollerRacerPawn::execThrottle },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PivotSpringArm_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SphereTrace_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetComponent_MetaData[] = {
		{ "Category", "Character" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshLocationComponent_MetaData[] = {
		{ "Category", "Character" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CheckForPlayerOnTrack_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveForce_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraHeight_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinCameraHeight_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ForwardMovement_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlowDown_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HitPoint_MetaData[] = {
		{ "Category", "RollerRacerPawn" },
		{ "ModuleRelativePath", "C++/RollerRacerPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PivotSpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SphereTrace;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshLocationComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CheckForPlayerOnTrack;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ThrottleAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SteeringAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveForce;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraHeight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinCameraHeight;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ForwardMovement;
	static void NewProp_SlowDown_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_SlowDown;
	static const UECodeGen_Private::FStructPropertyParams NewProp_HitPoint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraHeight, "AdjustCameraHeight" }, // 3462439477
		{ &Z_Construct_UFunction_ARollerRacerPawn_AdjustCameraRoll, "AdjustCameraRoll" }, // 1655334251
		{ &Z_Construct_UFunction_ARollerRacerPawn_ReleaseThrottle, "ReleaseThrottle" }, // 801782852
		{ &Z_Construct_UFunction_ARollerRacerPawn_SetForwardMovement, "SetForwardMovement" }, // 3406211085
		{ &Z_Construct_UFunction_ARollerRacerPawn_Steering, "Steering" }, // 2120729216
		{ &Z_Construct_UFunction_ARollerRacerPawn_Throttle, "Throttle" }, // 528557765
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARollerRacerPawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringArm_MetaData), NewProp_SpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_PivotSpringArm = { "PivotSpringArm", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, PivotSpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PivotSpringArm_MetaData), NewProp_PivotSpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SphereTrace = { "SphereTrace", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, SphereTrace), Z_Construct_UClass_USphereTrace_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SphereTrace_MetaData), NewProp_SphereTrace_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_TargetComponent = { "TargetComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, TargetComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetComponent_MetaData), NewProp_TargetComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MeshLocationComponent = { "MeshLocationComponent", nullptr, (EPropertyFlags)0x01140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, MeshLocationComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshLocationComponent_MetaData), NewProp_MeshLocationComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_CheckForPlayerOnTrack = { "CheckForPlayerOnTrack", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, CheckForPlayerOnTrack), Z_Construct_UClass_UCheckForPlayerOnTrack_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CheckForPlayerOnTrack_MetaData), NewProp_CheckForPlayerOnTrack_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ThrottleAction = { "ThrottleAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, ThrottleAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThrottleAction_MetaData), NewProp_ThrottleAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SteeringAction = { "SteeringAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, SteeringAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SteeringAction_MetaData), NewProp_SteeringAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MoveForce = { "MoveForce", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, MoveForce), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveForce_MetaData), NewProp_MoveForce_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_CameraHeight = { "CameraHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, CameraHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraHeight_MetaData), NewProp_CameraHeight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MinCameraHeight = { "MinCameraHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, MinCameraHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinCameraHeight_MetaData), NewProp_MinCameraHeight_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ForwardMovement = { "ForwardMovement", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, ForwardMovement), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ForwardMovement_MetaData), NewProp_ForwardMovement_MetaData) };
void Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SlowDown_SetBit(void* Obj)
{
	((ARollerRacerPawn*)Obj)->SlowDown = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SlowDown = { "SlowDown", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ARollerRacerPawn), &Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SlowDown_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlowDown_MetaData), NewProp_SlowDown_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_HitPoint = { "HitPoint", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPawn, HitPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HitPoint_MetaData), NewProp_HitPoint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARollerRacerPawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_PivotSpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SphereTrace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_TargetComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MeshLocationComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_CheckForPlayerOnTrack,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ThrottleAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SteeringAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MoveForce,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_CameraHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_MinCameraHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_ForwardMovement,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_SlowDown,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPawn_Statics::NewProp_HitPoint,
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
	FuncInfo,
	Z_Construct_UClass_ARollerRacerPawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
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
		{ Z_Construct_UClass_ARollerRacerPawn, ARollerRacerPawn::StaticClass, TEXT("ARollerRacerPawn"), &Z_Registration_Info_UClass_ARollerRacerPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARollerRacerPawn), 522137100U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_258261300(TEXT("/Script/RollerRacer"),
	Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
