// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RollerRacer/C++/SplineTrack.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSplineTrack() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_ASplineTrack();
ROLLERRACER_API UClass* Z_Construct_UClass_ASplineTrack_NoRegister();
UPackage* Z_Construct_UPackage__Script_RollerRacer();
// End Cross Module References

// Begin Class ASplineTrack
void ASplineTrack::StaticRegisterNativesASplineTrack()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASplineTrack);
UClass* Z_Construct_UClass_ASplineTrack_NoRegister()
{
	return ASplineTrack::StaticClass();
}
struct Z_Construct_UClass_ASplineTrack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "C++/SplineTrack.h" },
		{ "ModuleRelativePath", "C++/SplineTrack.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplineComponent_MetaData[] = {
		{ "Category", "Spline" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "C++/SplineTrack.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "Category", "Spline" },
		{ "ModuleRelativePath", "C++/SplineTrack.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SplineComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASplineTrack>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASplineTrack_Statics::NewProp_SplineComponent = { "SplineComponent", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASplineTrack, SplineComponent), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplineComponent_MetaData), NewProp_SplineComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASplineTrack_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASplineTrack, Mesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASplineTrack_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASplineTrack_Statics::NewProp_SplineComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASplineTrack_Statics::NewProp_Mesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASplineTrack_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASplineTrack_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_RollerRacer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASplineTrack_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASplineTrack_Statics::ClassParams = {
	&ASplineTrack::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASplineTrack_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASplineTrack_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASplineTrack_Statics::Class_MetaDataParams), Z_Construct_UClass_ASplineTrack_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASplineTrack()
{
	if (!Z_Registration_Info_UClass_ASplineTrack.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASplineTrack.OuterSingleton, Z_Construct_UClass_ASplineTrack_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASplineTrack.OuterSingleton;
}
template<> ROLLERRACER_API UClass* StaticClass<ASplineTrack>()
{
	return ASplineTrack::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASplineTrack);
ASplineTrack::~ASplineTrack() {}
// End Class ASplineTrack

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SplineTrack_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASplineTrack, ASplineTrack::StaticClass, TEXT("ASplineTrack"), &Z_Registration_Info_UClass_ASplineTrack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASplineTrack), 1882402405U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SplineTrack_h_1119742533(TEXT("/Script/RollerRacer"),
	Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SplineTrack_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_johnp_Documents_GitHub_RollerRacer_RollerRacer_Source_RollerRacer_C___SplineTrack_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
