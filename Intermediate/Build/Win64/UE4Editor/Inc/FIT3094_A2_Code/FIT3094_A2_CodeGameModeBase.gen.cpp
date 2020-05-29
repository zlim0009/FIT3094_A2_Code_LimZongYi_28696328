// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FIT3094_A2_Code/FIT3094_A2_CodeGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFIT3094_A2_CodeGameModeBase() {}
// Cross Module References
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_NoRegister();
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_FIT3094_A2_Code();
// End Cross Module References
	void AFIT3094_A2_CodeGameModeBase::StaticRegisterNativesAFIT3094_A2_CodeGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_NoRegister()
	{
		return AFIT3094_A2_CodeGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_FIT3094_A2_Code,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "FIT3094_A2_CodeGameModeBase.h" },
		{ "ModuleRelativePath", "FIT3094_A2_CodeGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFIT3094_A2_CodeGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics::ClassParams = {
		&AFIT3094_A2_CodeGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFIT3094_A2_CodeGameModeBase, 1867874947);
	template<> FIT3094_A2_CODE_API UClass* StaticClass<AFIT3094_A2_CodeGameModeBase>()
	{
		return AFIT3094_A2_CodeGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFIT3094_A2_CodeGameModeBase(Z_Construct_UClass_AFIT3094_A2_CodeGameModeBase, &AFIT3094_A2_CodeGameModeBase::StaticClass, TEXT("/Script/FIT3094_A2_Code"), TEXT("AFIT3094_A2_CodeGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFIT3094_A2_CodeGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
