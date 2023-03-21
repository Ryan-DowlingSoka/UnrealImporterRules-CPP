// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/IRManagerSubsystem.h"

#include "ImporterRulesDeveloperSettings.h"

void UIRManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	static FName ImporterRulesAppliedName = FName(TEXT("importer_rules_applied"));
	static FString TrueString = FString(TEXT("True"));
	SetImportedAssetTagAction = NewObject<UIRActionSetAssetTags>();
	SetImportedAssetTagAction->AssetTags.Add(ImporterRulesAppliedName, TrueString);
	CheckImportedAssetTagAction = NewObject<UIRQueryCheckAssetTag>();
	CheckImportedAssetTagAction->AssetTagKey = ImporterRulesAppliedName;
	CheckImportedAssetTagAction->AssetTagValue = TrueString;

	if (auto* ImportSubsystem = GEditor->GetEditorSubsystem<UImportSubsystem>())
	{
		ImportSubsystem->OnAssetPostImport.AddLambda([this](UFactory* Factory, UObject* CreatedObject)
		{
			check(IsValid(CheckImportedAssetTagAction) && IsValid(SetImportedAssetTagAction));
			const bool bIsReimport = CheckImportedAssetTagAction->Test(Factory, CreatedObject);
			UImporterRulesDeveloperSettings* DeveloperSettings = GetMutableDefault<UImporterRulesDeveloperSettings>();
			check(IsValid(DeveloperSettings));
			for (auto RulesIt = DeveloperSettings->RegisteredRules.CreateIterator(); RulesIt; ++RulesIt)
			{
				if (CreatedObject->IsA(RulesIt.Key()))
				{
					for (const auto Rule : RulesIt.Value().Rules)
					{
						if (!bIsReimport || Rule->bApplyOnReimport)
						{
							Rule->Apply(Factory, CreatedObject);
						}
					}
				}
			}
		});
	}
}

void UIRManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
