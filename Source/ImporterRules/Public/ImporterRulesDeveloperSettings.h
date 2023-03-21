// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rules/IRRuleBase.h"
#include "UObject/Object.h"
#include "ImporterRulesDeveloperSettings.generated.h"

USTRUCT(BlueprintType, DisplayName="Importer Rules Array")
struct FIRRulesArray
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	TArray<TObjectPtr<UIRRuleBase>> Rules;
};

/**
 * 
 */
UCLASS(config=Editor, DisplayName="Post Asset Import Rules")
class IMPORTERRULES_API UImporterRulesDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override {return FName("Project");}
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override {return FName("Editor");}
	
	UPROPERTY(Config, EditAnywhere, Category="Importer Rules")
	TMap<TSubclassOf<UObject>, FIRRulesArray> RegisteredRules;
};
