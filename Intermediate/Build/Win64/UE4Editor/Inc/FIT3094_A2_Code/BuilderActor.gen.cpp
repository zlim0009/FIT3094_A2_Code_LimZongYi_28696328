// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FIT3094_A2_Code/BuilderActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBuilderActor() {}
// Cross Module References
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_ABuilderActor_NoRegister();
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_ABuilderActor();
	FIT3094_A2_CODE_API UClass* Z_Construct_UClass_AGOAPActor();
	UPackage* Z_Construct_UPackage__Script_FIT3094_A2_Code();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void ABuilderActor::StaticRegisterNativesABuilderActor()
	{
	}
	UClass* Z_Construct_UClass_ABuilderActor_NoRegister()
	{
		return ABuilderActor::StaticClass();
	}
	struct Z_Construct_UClass_ABuilderActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumStoneResources_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_NumStoneResources;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumWoodResources_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_NumWoodResources;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Health_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_Health;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_VisibleComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_VisibleComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABuilderActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGOAPActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FIT3094_A2_Code,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABuilderActor_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "BuilderActor.h" },
		{ "ModuleRelativePath", "BuilderActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumStoneResources_MetaData[] = {
		{ "Category", "Resources" },
		{ "Comment", "// Number of stone resources does this actor hold currently\n" },
		{ "ModuleRelativePath", "BuilderActor.h" },
		{ "ToolTip", "Number of stone resources does this actor hold currently" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumStoneResources = { "NumStoneResources", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABuilderActor, NumStoneResources), METADATA_PARAMS(Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumStoneResources_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumStoneResources_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumWoodResources_MetaData[] = {
		{ "Category", "Resources" },
		{ "Comment", "// Number of wood resources does this actor hold currently\n" },
		{ "ModuleRelativePath", "BuilderActor.h" },
		{ "ToolTip", "Number of wood resources does this actor hold currently" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumWoodResources = { "NumWoodResources", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABuilderActor, NumWoodResources), METADATA_PARAMS(Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumWoodResources_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumWoodResources_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABuilderActor_Statics::NewProp_Health_MetaData[] = {
		{ "Category", "Health" },
		{ "ModuleRelativePath", "BuilderActor.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ABuilderActor_Statics::NewProp_Health = { "Health", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABuilderActor, Health), METADATA_PARAMS(Z_Construct_UClass_ABuilderActor_Statics::NewProp_Health_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABuilderActor_Statics::NewProp_Health_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABuilderActor_Statics::NewProp_VisibleComponent_MetaData[] = {
		{ "Category", "BuilderActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "BuilderActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABuilderActor_Statics::NewProp_VisibleComponent = { "VisibleComponent", nullptr, (EPropertyFlags)0x0040000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABuilderActor, VisibleComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABuilderActor_Statics::NewProp_VisibleComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABuilderActor_Statics::NewProp_VisibleComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABuilderActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumStoneResources,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABuilderActor_Statics::NewProp_NumWoodResources,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABuilderActor_Statics::NewProp_Health,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABuilderActor_Statics::NewProp_VisibleComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABuilderActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABuilderActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ABuilderActor_Statics::ClassParams = {
		&ABuilderActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABuilderActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ABuilderActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ABuilderActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABuilderActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABuilderActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ABuilderActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ABuilderActor, 3182311666);
	template<> FIT3094_A2_CODE_API UClass* StaticClass<ABuilderActor>()
	{
		return ABuilderActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ABuilderActor(Z_Construct_UClass_ABuilderActor, &ABuilderActor::StaticClass, TEXT("/Script/FIT3094_A2_Code"), TEXT("ABuilderActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABuilderActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
