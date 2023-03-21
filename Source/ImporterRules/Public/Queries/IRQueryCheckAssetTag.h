// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IRQueryBase.h"
#include "UObject/Object.h"
#include "IRQueryCheckAssetTag.generated.h"

/**
 * 
 */
UCLASS(DisplayName="Check Asset Tag Query")
class IMPORTERRULES_API UIRQueryCheckAssetTag : public UIRQueryBase
{
	GENERATED_BODY()

public:
	virtual bool Test_Implementation(UFactory* Factor, UObject* CreatedObject) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules", meta=(ExposeOnSpawn))
	FName AssetTagKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules", meta=(ExposeOnSpawn))
	FString AssetTagValue;
};
