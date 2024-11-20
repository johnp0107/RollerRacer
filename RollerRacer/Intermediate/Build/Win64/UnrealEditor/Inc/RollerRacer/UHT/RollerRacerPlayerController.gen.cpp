// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RollerRacer/C++/RollerRacerPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRollerRacerPlayerController() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
ROLLERRACER_API UClass* Z_Construct_UClass_ARollerRacerPlayerController();
ROLLERRACER_API UClass* Z_Construct_UClass_ARollerRacerPlayerController_NoRegister();
UPackage* Z_Construct_UPackage__Script_RollerRacer();
// End Cross Module References

// Begin Class ARollerRacerPlayerController
void ARollerRacerPlayerController::StaticRegisterNativesARollerRacerPlayerController()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARollerRacerPlayerController);
UClass* Z_Construct_UClass_ARollerRacerPlayerController_NoRegister()
{
	return ARollerRacerPlayerController::StaticClass();
}
struct Z_Construct_UClass_ARollerRacerPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "C++/RollerRacerPlayerController.h" },
		{ "ModuleRelativePath", "C++/RollerRacerPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Mapping Context to be used for player input */" },
#endif
		{ "ModuleRelativePath", "C++/RollerRacerPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Mapping Context to be used for player input" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InputMappingContext;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARollerRacerPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARollerRacerPlayerController_Statics::NewProp_InputMappingContext = { "InputMappingContext", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARollerRacerPlayerController, InputMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputMappingContext_MetaData), NewProp_InputMappingContext_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARollerRacerPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARollerRacerPlayerController_Statics::NewProp_InputMappingContext,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ARollerRacerPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_RollerRacer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ARollerRacerPlayerController_Statics::ClassParams = {
	&ARollerRacerPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ARollerRacerPlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPlayerController_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARollerRacerPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ARollerRacerPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ARollerRacerPlayerController()
{
	if (!Z_Registration_Info_UClass_ARollerRacerPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARollerRacerPlayerController.OuterSingleton, Z_Construct_UClass_ARollerRacerPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ARollerRacerPlayerController.OuterSingleton;
}
template<> ROLLERRACER_API UClass* StaticClass<ARollerRacerPlayerController>()
{
	return ARollerRacerPlayerController::StaticClass();
}
ARollerRacerPlayerController::ARollerRacerPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ARollerRacerPlayerController);
ARollerRacerPlayerController::~ARollerRacerPlayerController() {}
// End Class ARollerRacerPlayerController

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPlayerController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ARollerRacerPlayerController, ARollerRacerPlayerController::StaticClass, TEXT("ARollerRacerPlayerController"), &Z_Registration_Info_UClass_ARollerRacerPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARollerRacerPlayerController), 2201709755U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPlayerController_h_2311535678(TEXT("/Script/RollerRacer"),
	Z_CompiledInDeferFile_FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPlayerController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
