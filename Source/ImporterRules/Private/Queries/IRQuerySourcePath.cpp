/* MIT License
 * 
 * Copyright (c) 2023 Ryan DowlingSoka
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and//or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
