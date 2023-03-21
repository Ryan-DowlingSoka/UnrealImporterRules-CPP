// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IRQueryBase.h"
#include "UObject/Object.h"
#include "IRQueryDestinationPath.generated.h"

/**
 * 
 */
UCLASS(DisplayName="Destination Path Contains")
class IMPORTERRULES_API UIRQueryDestinationPathContains : public UIRQueryBase
{
	GENERATED_BODY()
public:
	virtual bool Test_Implementation(UFactory* Factor, UObject* CreatedObject) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	FString Contains;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	bool bCaseSensitive;
};
