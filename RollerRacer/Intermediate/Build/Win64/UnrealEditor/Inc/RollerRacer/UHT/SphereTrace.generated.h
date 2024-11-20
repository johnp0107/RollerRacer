// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "C++/SphereTrace.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ROLLERRACER_SphereTrace_generated_h
#error "SphereTrace.generated.h already included, missing '#pragma once' in SphereTrace.h"
#endif
#define ROLLERRACER_SphereTrace_generated_h

#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAdjustPlayerPosition); \
	DECLARE_FUNCTION(execGetDirectionBetweenPoints);


#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSphereTrace(); \
	friend struct Z_Construct_UClass_USphereTrace_Statics; \
public: \
	DECLARE_CLASS(USphereTrace, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/RollerRacer"), NO_API) \
	DECLARE_SERIALIZER(USphereTrace)


#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	USphereTrace(USphereTrace&&); \
	USphereTrace(const USphereTrace&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USphereTrace); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USphereTrace); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USphereTrace) \
	NO_API virtual ~USphereTrace();


#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_10_PROLOG
#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_13_INCLASS_NO_PURE_DECLS \
	FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ROLLERRACER_API UClass* StaticClass<class USphereTrace>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___SphereTrace_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
