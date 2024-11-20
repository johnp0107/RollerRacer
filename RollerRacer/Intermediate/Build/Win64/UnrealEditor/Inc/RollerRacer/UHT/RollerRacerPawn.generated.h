// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "C++/RollerRacerPawn.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FInputActionValue;
#ifdef ROLLERRACER_RollerRacerPawn_generated_h
#error "RollerRacerPawn.generated.h already included, missing '#pragma once' in RollerRacerPawn.h"
#endif
#define ROLLERRACER_RollerRacerPawn_generated_h

#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAdjustCameraRoll); \
	DECLARE_FUNCTION(execAdjustCameraHeight); \
	DECLARE_FUNCTION(execSteering); \
	DECLARE_FUNCTION(execReleaseThrottle); \
	DECLARE_FUNCTION(execThrottle);


#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARollerRacerPawn(); \
	friend struct Z_Construct_UClass_ARollerRacerPawn_Statics; \
public: \
	DECLARE_CLASS(ARollerRacerPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/RollerRacer"), NO_API) \
	DECLARE_SERIALIZER(ARollerRacerPawn)


#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ARollerRacerPawn(ARollerRacerPawn&&); \
	ARollerRacerPawn(const ARollerRacerPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARollerRacerPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARollerRacerPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARollerRacerPawn) \
	NO_API virtual ~ARollerRacerPawn();


#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_17_PROLOG
#define FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_20_INCLASS_NO_PURE_DECLS \
	FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ROLLERRACER_API UClass* StaticClass<class ARollerRacerPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_johnp_Documents_Unreal_Projects_RollerRacer_Source_RollerRacer_C___RollerRacerPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
