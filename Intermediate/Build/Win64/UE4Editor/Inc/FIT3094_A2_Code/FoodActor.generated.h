// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef FIT3094_A2_CODE_FoodActor_generated_h
#error "FoodActor.generated.h already included, missing '#pragma once' in FoodActor.h"
#endif
#define FIT3094_A2_CODE_FoodActor_generated_h

#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_SPARSE_DATA
#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnOverlapBegin) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnOverlapBegin(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnOverlapBegin) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnOverlapBegin(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFoodActor(); \
	friend struct Z_Construct_UClass_AFoodActor_Statics; \
public: \
	DECLARE_CLASS(AFoodActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FIT3094_A2_Code"), NO_API) \
	DECLARE_SERIALIZER(AFoodActor)


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAFoodActor(); \
	friend struct Z_Construct_UClass_AFoodActor_Statics; \
public: \
	DECLARE_CLASS(AFoodActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FIT3094_A2_Code"), NO_API) \
	DECLARE_SERIALIZER(AFoodActor)


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AFoodActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AFoodActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFoodActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFoodActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFoodActor(AFoodActor&&); \
	NO_API AFoodActor(const AFoodActor&); \
public:


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFoodActor(AFoodActor&&); \
	NO_API AFoodActor(const AFoodActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFoodActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFoodActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFoodActor)


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__VisibleComponent() { return STRUCT_OFFSET(AFoodActor, VisibleComponent); } \
	FORCEINLINE static uint32 __PPO__CollisionComponent() { return STRUCT_OFFSET(AFoodActor, CollisionComponent); }


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_11_PROLOG
#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_PRIVATE_PROPERTY_OFFSET \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_SPARSE_DATA \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_RPC_WRAPPERS \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_INCLASS \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_PRIVATE_PROPERTY_OFFSET \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_SPARSE_DATA \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_INCLASS_NO_PURE_DECLS \
	FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FIT3094_A2_CODE_API UClass* StaticClass<class AFoodActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FIT3094_A2_Code_LimZongYi_28696328_Source_FIT3094_A2_Code_FoodActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
