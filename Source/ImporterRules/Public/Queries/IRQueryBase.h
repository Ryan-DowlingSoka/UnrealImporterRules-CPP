// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IRQueryBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType, DisplayName="Post Import Query Base", AutoExpandCategories=("Importer Rules"), CollapseCategories)
class IMPORTERRULES_API UIRQueryBase : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, Category="Importer Rules")
	bool Test(class UFactory* Factor, UObject* CreatedObject);
};
