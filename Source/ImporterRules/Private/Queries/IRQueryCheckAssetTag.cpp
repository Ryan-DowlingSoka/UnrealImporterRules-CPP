// Fill out your copyright notice in the Description page of Project Settings.


#include "Queries/IRQueryCheckAssetTag.h"

#include "Subsystems/EditorAssetSubsystem.h"

bool UIRQueryCheckAssetTag::Test_Implementation(UFactory* Factor, UObject* CreatedObject)
{
	if(AssetTagKey == NAME_None)
	{
		return false;
	}
	
	if(IsValid(CreatedObject))
	{
		if(UEditorAssetSubsystem* EditorAssetSubsystem = GEditor->GetEditorSubsystem<UEditorAssetSubsystem>())
		{
			const FString Value = EditorAssetSubsystem->GetMetadataTag(CreatedObject, AssetTagKey);
			if( Value.IsEmpty() )
			{
				return false;
			}
			
			return AssetTagValue.IsEmpty() || AssetTagValue == Value;
		}
	}
	return false;
}
