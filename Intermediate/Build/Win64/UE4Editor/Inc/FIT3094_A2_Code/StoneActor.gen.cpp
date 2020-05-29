// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FIT3094_A2_Code/StoneActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStoneActor() {}
// Cross Module References
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_AStoneActor_NoRegister();
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_AStoneActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FIT3094_A2_Code();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void AStoneActor::StaticRegisterNativesAStoneActor()
	{
	}
	UClass* Z_Construct_UClass_AStoneActor_NoRegister()
	{
		return AStoneActor::StaticClass();
	}
	struct Z_Construct_UClass_AStoneActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StoneResources_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_StoneResources;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_VisibleComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_VisibleComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AStoneActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FIT3094_A2_Code,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStoneActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "StoneActor.h" },
		{ "ModuleRelativePath", "StoneActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStoneActor_Statics::NewProp_StoneResources_MetaData[] = {
		{ "Category", "Resources" },
		{ "ModuleRelativePath", "StoneActor.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AStoneActor_Statics::NewProp_StoneResources = { "StoneResources", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStoneActor, StoneResources), METADATA_PARAMS(Z_Construct_UClass_AStoneActor_Statics::NewProp_StoneResources_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStoneActor_Statics::NewProp_StoneResources_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStoneActor_Statics::NewProp_VisibleComponent_MetaData[] = {
		{ "Category", "StoneActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "StoneActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStoneActor_Statics::NewProp_VisibleComponent = { "VisibleComponent", nullptr, (EPropertyFlags)0x0040000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStoneActor, VisibleComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AStoneActor_Statics::NewProp_VisibleComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AStoneActor_Statics::NewProp_VisibleComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AStoneActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStoneActor_Statics::NewProp_StoneResources,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStoneActor_Statics::NewProp_VisibleComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AStoneActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStoneActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AStoneActor_Statics::ClassParams = {
		&AStoneActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AStoneActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AStoneActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AStoneActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AStoneActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AStoneActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AStoneActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AStoneActor, 385470210);
	template<> FIT3094_A2_CODE_API UClass* StaticClass<AStoneActor>()
	{
		return AStoneActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AStoneActor(Z_Construct_UClass_AStoneActor, &AStoneActor::StaticClass, TEXT("/Script/FIT3094_A2_Code"), TEXT("AStoneActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AStoneActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
