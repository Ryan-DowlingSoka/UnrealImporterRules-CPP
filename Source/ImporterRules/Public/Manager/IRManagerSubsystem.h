// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/IRActionSetAssetTags.h"
#include "Queries/IRQueryCheckAssetTag.h"
#include "Rules/IRRuleBase.h"
#include "UObject/Object.h"
#include "IRManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, CollapseCategories)
class IMPORTERRULES_API UIRManagerSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	// Begin UEditorSubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End UEditorSubsystem Interface
	
private:
	UPROPERTY(Transient)
	TObjectPtr<UIRActionSetAssetTags> SetImportedAssetTagAction;

	UPROPERTY(Transient)
	TObjectPtr<UIRQueryCheckAssetTag> CheckImportedAssetTagAction;
};
