// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IRActionBase.h"
#include "UObject/Object.h"
#include "IRActionSetAssetTags.generated.h"

/**
 * 
 */
UCLASS(DisplayName="Set Asset Tags Action")
class IMPORTERRULES_API UIRActionSetAssetTags : public UIRActionBase
{
	GENERATED_BODY()

public:
	virtual bool Apply_Implementation(UFactory* Factory, UObject* CreatedObject) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules", meta=(ExposeOnSpawn, MultiLine))
	TMap<FName, FString> AssetTags;
};
