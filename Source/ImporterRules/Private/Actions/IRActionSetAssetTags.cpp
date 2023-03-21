// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/IRActionSetAssetTags.h"

#include "Subsystems/EditorAssetSubsystem.h"

bool UIRActionSetAssetTags::Apply_Implementation(UFactory* Factory, UObject* CreatedObject)
{
	if(IsValid(CreatedObject))
	{
		if(UEditorAssetSubsystem* EditorAssetSubsystem = GEditor->GetEditorSubsystem<UEditorAssetSubsystem>())
		{
			for(TTuple<FName, FString>& AssetTag : AssetTags )
			{
				if(AssetTag.Key == NAME_None || AssetTag.Value.IsEmpty())
					continue;
					
				EditorAssetSubsystem->SetMetadataTag(CreatedObject, AssetTag.Key, AssetTag.Value);
			}
			return true;
		}
	}
	return false;
}
