// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FIT3094_A2_Code/GOAPActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGOAPActor() {}
// Cross Module References
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_AGOAPActor_NoRegister();
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_AGOAPActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FIT3094_A2_Code();
// End Cross Module References
	void AGOAPActor::StaticRegisterNativesAGOAPActor()
	{
	}
	UClass* Z_Construct_UClass_AGOAPActor_NoRegister()
	{
		return AGOAPActor::StaticClass();
	}
	struct Z_Construct_UClass_AGOAPActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGOAPActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FIT3094_A2_Code,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGOAPActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GOAPActor.h" },
		{ "ModuleRelativePath", "GOAPActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGOAPActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGOAPActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGOAPActor_Statics::ClassParams = {
		&AGOAPActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGOAPActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGOAPActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGOAPActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGOAPActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGOAPActor, 128611478);
	template<> FIT3094_A2_CODE_API UClass* StaticClass<AGOAPActor>()
	{
		return AGOAPActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGOAPActor(Z_Construct_UClass_AGOAPActor, &AGOAPActor::StaticClass, TEXT("/Script/FIT3094_A2_Code"), TEXT("AGOAPActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGOAPActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
