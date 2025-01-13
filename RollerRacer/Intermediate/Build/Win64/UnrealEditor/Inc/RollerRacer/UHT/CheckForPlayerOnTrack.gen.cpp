// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RollerRacer/C++/CheckForPlayerOnTrack.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCheckForPlayerOnTrack() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
ROLLERRACER_API UClass* Z_Construct_UClass_UCheckForPlayerOnTrack();
ROLLERRACER_API UClass* Z_Construct_UClass_UCheckForPlayerOnTrack_NoRegister();
UPackage* Z_Construct_UPackage__Script_RollerRacer();
// End Cross Module References

// Begin Class UCheckForPlayerOnTrack Function PlacePlayerBackOnFloor
struct Z_Construct_UFunction_UCheckForPlayerOnTrack_PlacePlayerBackOnFloor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/CheckForPlayerOnTrack.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCheckForPlayerOnTrack_PlacePlayerBackOnFloor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCheckForPlayerOnTrack, nullptr, "PlacePlayerBackOnFloor", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCheckForPlayerOnTrack_PlacePlayerBackOnFloor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCheckForPlayerOnTrack_PlacePlayerBackOnFloor_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UCheckForPlayerOnTrack_PlacePlayerBackOnFloor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCheckForPlayerOnTrack_PlacePlayerBackOnFloor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCheckForPlayerOnTrack::execPlacePlayerBackOnFloor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlacePlayerBackOnFloor();
	P_NATIVE_END;
}
// End Class UCheckForPlayerOnTrack Function PlacePlayerBackOnFloor

// Begin Class UCheckForPlayerOnTrack Function SphereTraceToFloor
struct Z_Construct_UFunction_UCheckForPlayerOnTrack_SphereTraceToFloor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "C++/CheckForPlayerOnTrack.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCheckForPlayerOnTrack_SphereTraceToFloor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCheckForPlayerOnTrack, nullptr, "SphereTraceToFloor", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCheckForPlayerOnTrack_SphereTraceToFloor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCheckForPlayerOnTrack_SphereTraceToFloor_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UCheckForPlayerOnTrack_SphereTraceToFloor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCheckForPlayerOnTrack_SphereTraceToFloor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UCheckForPlayerOnTrack::execSphereTraceToFloor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SphereTraceToFloor();
	P_NATIVE_END;
}
// End Class UCheckForPlayerOnTrack Function SphereTraceToFloor

// Begin Class UCheckForPlayerOnTrack
void UCheckForPlayerOnTrack::StaticRegisterNativesUCheckForPlayerOnTrack()
{
	UClass* Class = UCheckForPlayerOnTrack::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "PlacePlayerBackOnFloor", &UCheckForPlayerOnTrack::execPlacePlayerBackOnFloor },
		{ "SphereTraceToFloor", &UCheckForPlayerOnTrack::execSphereTraceToFloor },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCheckForPlayerOnTrack);
UClass* Z_Construct_UClass_UCheckForPlayerOnTrack_NoRegister()
{
	return UCheckForPlayerOnTrack::StaticClass();
}
struct Z_Construct_UClass_UCheckForPlayerOnTrack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "C++/CheckForPlayerOnTrack.h" },
		{ "ModuleRelativePath", "C++/CheckForPlayerOnTrack.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Center_MetaData[] = {
		{ "Category", "CheckForPlayerOnTrack" },
		{ "ModuleRelativePath", "C++/CheckForPlayerOnTrack.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerOnFloor_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "C++/CheckForPlayerOnTrack.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Center;
	static void NewProp_PlayerOnFloor_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_PlayerOnFloor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCheckForPlayerOnTrack_PlacePlayerBackOnFloor, "PlacePlayerBackOnFloor" }, // 1822143348
		{ &Z_Construct_UFunction_UCheckForPlayerOnTrack_SphereTraceToFloor, "SphereTraceToFloor" }, // 1329792597
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCheckForPlayerOnTrack>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::NewProp_Center = { "Center", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCheckForPlayerOnTrack, Center), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Center_MetaData), NewProp_Center_MetaData) };
void Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::NewProp_PlayerOnFloor_SetBit(void* Obj)
{
	((UCheckForPlayerOnTrack*)Obj)->PlayerOnFloor = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::NewProp_PlayerOnFloor = { "PlayerOnFloor", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCheckForPlayerOnTrack), &Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::NewProp_PlayerOnFloor_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerOnFloor_MetaData), NewProp_PlayerOnFloor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::NewProp_Center,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::NewProp_PlayerOnFloor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_RollerRacer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::ClassParams = {
	&UCheckForPlayerOnTrack::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::Class_MetaDataParams), Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCheckForPlayerOnTrack()
{
	if (!Z_Registration_Info_UClass_UCheckForPlayerOnTrack.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCheckForPlayerOnTrack.OuterSingleton, Z_Construct_UClass_UCheckForPlayerOnTrack_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCheckForPlayerOnTrack.OuterSingleton;
}
template<> ROLLERRACER_API UClass* StaticClass<UCheckForPlayerOnTrack>()
{
	return UCheckForPlayerOnTrack::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCheckForPlayerOnTrack);
UCheckForPlayerOnTrack::~UCheckForPlayerOnTrack() {}
// End Class UCheckForPlayerOnTrack

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___CheckForPlayerOnTrack_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCheckForPlayerOnTrack, UCheckForPlayerOnTrack::StaticClass, TEXT("UCheckForPlayerOnTrack"), &Z_Registration_Info_UClass_UCheckForPlayerOnTrack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCheckForPlayerOnTrack), 1353305079U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___CheckForPlayerOnTrack_h_902901688(TEXT("/Script/RollerRacer"),
	Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___CheckForPlayerOnTrack_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___CheckForPlayerOnTrack_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
