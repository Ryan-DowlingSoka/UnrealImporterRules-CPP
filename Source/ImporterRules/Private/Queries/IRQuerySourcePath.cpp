// Fill out your copyright notice in the Description page of Project Settings.


#include "Queries/IRQuerySourcePath.h"

#include "EditorFramework/AssetImportData.h"
#include "UObject/PropertyAccessUtil.h"

bool UIRQuerySourcePathBase::GetSourcePath(const UObject* CreatedObject, FString& OutPath) const
{
	if(!IsValid(CreatedObject))
		return false;
	
	const FProperty* FoundProperty = PropertyAccessUtil::FindPropertyByName(GET_MEMBER_NAME_CHECKED(UTexture2D, AssetImportData), CreatedObject->GetClass());
	if(FoundProperty)
	{
		const FProperty* ValueProp = nullptr;
		void* ValuePtr = nullptr;
		const EPropertyAccessResultFlags AccessResult = PropertyAccessUtil::GetPropertyValue_Object(FoundProperty, CreatedObject, ValueProp, ValuePtr, INDEX_NONE);
		if(AccessResult == EPropertyAccessResultFlags::Success)
		{
			const UAssetImportData* AssetImportData = ((const UAssetImportData*)ValuePtr);
			OutPath = AssetImportData->GetFirstFilename();
			return true;
		}
	}
	return false;
}

bool UIRQuerySourceFilenameStartsWith::Test_Implementation(UFactory* Factor, UObject* CreatedObject)
{
	FString SourcePath;
	if(GetSourcePath(CreatedObject, SourcePath))
	{
		const FString Filename = FPaths::GetBaseFilename(SourcePath);
		return Filename.StartsWith(StartsWith, bCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase);
	}
	return false;
}

bool UIRQuerySourceFilenameEndsWith::Test_Implementation(UFactory* Factor, UObject* CreatedObject)
{
	FString SourcePath;
	if(GetSourcePath(CreatedObject, SourcePath))
	{
		const FString Filename = FPaths::GetBaseFilename(SourcePath);
		return Filename.EndsWith(EndsWith, bCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase);
	}
	return false;
}

bool UIRQuerySourcePathContains::Test_Implementation(UFactory* Factor, UObject* CreatedObject)
{
	FString SourcePath;
	if(GetSourcePath(CreatedObject, SourcePath))
	{
		const FString Filename = FPaths::GetBaseFilename(SourcePath);
		return Filename.Contains(Contains, bCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase);
	}
	return false;
}

bool UIRQuerySourceExtensionMatches::Test_Implementation(UFactory* Factor, UObject* CreatedObject)
{
	FString SourcePath;
	if(GetSourcePath(CreatedObject, SourcePath))
	{
		const FString Extension = FPaths::GetExtension(SourcePath);
		TArray<FString> ValidExtensionsArray;
		ValidExtensions.Replace(TEXT("."), TEXT("")).ParseIntoArray(ValidExtensionsArray,TEXT(","));
		for(FString& Ext : ValidExtensionsArray)
		{
			if(Ext.Contains(Extension,bCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase))
			{
				return true;
			}
		}
	}
	return false;
}
