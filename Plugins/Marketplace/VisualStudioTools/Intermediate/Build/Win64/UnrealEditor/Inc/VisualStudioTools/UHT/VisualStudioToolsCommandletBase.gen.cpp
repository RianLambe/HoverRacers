// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VisualStudioTools/Private/VisualStudioToolsCommandletBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVisualStudioToolsCommandletBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UCommandlet();
	UPackage* Z_Construct_UPackage__Script_VisualStudioTools();
	VISUALSTUDIOTOOLS_API UClass* Z_Construct_UClass_UVisualStudioToolsCommandletBase();
	VISUALSTUDIOTOOLS_API UClass* Z_Construct_UClass_UVisualStudioToolsCommandletBase_NoRegister();
// End Cross Module References
	void UVisualStudioToolsCommandletBase::StaticRegisterNativesUVisualStudioToolsCommandletBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVisualStudioToolsCommandletBase);
	UClass* Z_Construct_UClass_UVisualStudioToolsCommandletBase_NoRegister()
	{
		return UVisualStudioToolsCommandletBase::StaticClass();
	}
	struct Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCommandlet,
		(UObject* (*)())Z_Construct_UPackage__Script_VisualStudioTools,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "VisualStudioToolsCommandletBase.h" },
		{ "ModuleRelativePath", "Private/VisualStudioToolsCommandletBase.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVisualStudioToolsCommandletBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::ClassParams = {
		&UVisualStudioToolsCommandletBase::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A9u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UVisualStudioToolsCommandletBase()
	{
		if (!Z_Registration_Info_UClass_UVisualStudioToolsCommandletBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVisualStudioToolsCommandletBase.OuterSingleton, Z_Construct_UClass_UVisualStudioToolsCommandletBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UVisualStudioToolsCommandletBase.OuterSingleton;
	}
	template<> VISUALSTUDIOTOOLS_API UClass* StaticClass<UVisualStudioToolsCommandletBase>()
	{
		return UVisualStudioToolsCommandletBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVisualStudioToolsCommandletBase);
	UVisualStudioToolsCommandletBase::~UVisualStudioToolsCommandletBase() {}
	struct Z_CompiledInDeferFile_FID_Users_rianl_Documents_GitHub_DingleSting_PodRacing_Plugins_Marketplace_VisualStudioTools_Source_VisualStudioTools_Private_VisualStudioToolsCommandletBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_rianl_Documents_GitHub_DingleSting_PodRacing_Plugins_Marketplace_VisualStudioTools_Source_VisualStudioTools_Private_VisualStudioToolsCommandletBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UVisualStudioToolsCommandletBase, UVisualStudioToolsCommandletBase::StaticClass, TEXT("UVisualStudioToolsCommandletBase"), &Z_Registration_Info_UClass_UVisualStudioToolsCommandletBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVisualStudioToolsCommandletBase), 1633684209U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_rianl_Documents_GitHub_DingleSting_PodRacing_Plugins_Marketplace_VisualStudioTools_Source_VisualStudioTools_Private_VisualStudioToolsCommandletBase_h_36662527(TEXT("/Script/VisualStudioTools"),
		Z_CompiledInDeferFile_FID_Users_rianl_Documents_GitHub_DingleSting_PodRacing_Plugins_Marketplace_VisualStudioTools_Source_VisualStudioTools_Private_VisualStudioToolsCommandletBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_rianl_Documents_GitHub_DingleSting_PodRacing_Plugins_Marketplace_VisualStudioTools_Source_VisualStudioTools_Private_VisualStudioToolsCommandletBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
