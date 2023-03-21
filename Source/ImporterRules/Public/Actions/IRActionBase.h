// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IRActionBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType, DisplayName="Post Import Action Base", AutoExpandCategories=("Importer Rules"), CollapseCategories)
class IMPORTERRULES_API UIRActionBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	bool Apply(class UFactory* Factory, UObject* CreatedObject);
};