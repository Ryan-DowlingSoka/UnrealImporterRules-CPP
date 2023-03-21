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
