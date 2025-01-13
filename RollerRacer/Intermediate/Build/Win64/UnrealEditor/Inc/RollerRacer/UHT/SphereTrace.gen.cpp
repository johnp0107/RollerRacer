// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RollerRacer/C++/SphereTrace.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSphereTrace() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
ROLLERRACER_API UClass* Z_Construct_UClass_USphereTrace();
ROLLERRACER_API UClass* Z_Construct_UClass_USphereTrace_NoRegister();
UPackage* Z_Construct_UPackage__Script_RollerRacer();
// End Cross Module References

// Begin Class USphereTrace Function AdjustPlayerPosition
struct Z_Construct_UFunction_USphereTrace_AdjustPlayerPosition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/SphereTrace.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USphereTrace_AdjustPlayerPosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USphereTrace, nullptr, "AdjustPlayerPosition", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USphereTrace_AdjustPlayerPosition_Statics::Function_MetaDataParams), Z_Construct_UFunction_USphereTrace_AdjustPlayerPosition_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_USphereTrace_AdjustPlayerPosition()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USphereTrace_AdjustPlayerPosition_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USphereTrace::execAdjustPlayerPosition)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AdjustPlayerPosition();
	P_NATIVE_END;
}
// End Class USphereTrace Function AdjustPlayerPosition

// Begin Class USphereTrace Function GetDirectionBetweenPoints
struct Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics
{
	struct SphereTrace_eventGetDirectionBetweenPoints_Parms
	{
		FVector PointA;
		FVector PointB;
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/SphereTrace.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PointA_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PointB_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_PointA;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PointB;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::NewProp_PointA = { "PointA", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SphereTrace_eventGetDirectionBetweenPoints_Parms, PointA), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PointA_MetaData), NewProp_PointA_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::NewProp_PointB = { "PointB", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SphereTrace_eventGetDirectionBetweenPoints_Parms, PointB), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PointB_MetaData), NewProp_PointB_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SphereTrace_eventGetDirectionBetweenPoints_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::NewProp_PointA,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::NewProp_PointB,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USphereTrace, nullptr, "GetDirectionBetweenPoints", nullptr, nullptr, Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::PropPointers), sizeof(Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::SphereTrace_eventGetDirectionBetweenPoints_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::Function_MetaDataParams), Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::SphereTrace_eventGetDirectionBetweenPoints_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USphereTrace::execGetDirectionBetweenPoints)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_PointA);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_PointB);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetDirectionBetweenPoints(Z_Param_Out_PointA,Z_Param_Out_PointB);
	P_NATIVE_END;
}
// End Class USphereTrace Function GetDirectionBetweenPoints

// Begin Class USphereTrace
void USphereTrace::StaticRegisterNativesUSphereTrace()
{
	UClass* Class = USphereTrace::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AdjustPlayerPosition", &USphereTrace::execAdjustPlayerPosition },
		{ "GetDirectionBetweenPoints", &USphereTrace::execGetDirectionBetweenPoints },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USphereTrace);
UClass* Z_Construct_UClass_USphereTrace_NoRegister()
{
	return USphereTrace::StaticClass();
}
struct Z_Construct_UClass_USphereTrace_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "C++/SphereTrace.h" },
		{ "ModuleRelativePath", "C++/SphereTrace.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TraceRadius_MetaData[] = {
		{ "Category", "Trace" },
		{ "ModuleRelativePath", "C++/SphereTrace.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TraceRadius;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USphereTrace_AdjustPlayerPosition, "AdjustPlayerPosition" }, // 128109561
		{ &Z_Construct_UFunction_USphereTrace_GetDirectionBetweenPoints, "GetDirectionBetweenPoints" }, // 4239630601
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USphereTrace>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USphereTrace_Statics::NewProp_TraceRadius = { "TraceRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USphereTrace, TraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TraceRadius_MetaData), NewProp_TraceRadius_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USphereTrace_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USphereTrace_Statics::NewProp_TraceRadius,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USphereTrace_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USphereTrace_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_RollerRacer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USphereTrace_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USphereTrace_Statics::ClassParams = {
	&USphereTrace::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USphereTrace_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USphereTrace_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USphereTrace_Statics::Class_MetaDataParams), Z_Construct_UClass_USphereTrace_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USphereTrace()
{
	if (!Z_Registration_Info_UClass_USphereTrace.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USphereTrace.OuterSingleton, Z_Construct_UClass_USphereTrace_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USphereTrace.OuterSingleton;
}
template<> ROLLERRACER_API UClass* StaticClass<USphereTrace>()
{
	return USphereTrace::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USphereTrace);
USphereTrace::~USphereTrace() {}
// End Class USphereTrace

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SphereTrace_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USphereTrace, USphereTrace::StaticClass, TEXT("USphereTrace"), &Z_Registration_Info_UClass_USphereTrace, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USphereTrace), 3922864848U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SphereTrace_h_3447040511(TEXT("/Script/RollerRacer"),
	Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SphereTrace_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SphereTrace_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
