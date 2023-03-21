// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IRQueryBase.h"
#include "UObject/Object.h"
#include "IRQuerySourcePath.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class IMPORTERRULES_API UIRQuerySourcePathBase : public UIRQueryBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	bool bCaseSensitive;

protected:
	UFUNCTION(BlueprintCallable, Category="Importer Rules")
	bool GetSourcePath(const UObject* CreatedObject, FString& OutPath) const;
};

/**
 * 
 */
UCLASS(DisplayName="Source Filename Starts With")
class IMPORTERRULES_API UIRQuerySourceFilenameStartsWith : public UIRQuerySourcePathBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	FString StartsWith;
	
	virtual bool Test_Implementation(UFactory* Factor, UObject* CreatedObject) override;
};

UCLASS(DisplayName="Source Filename Ends With")
class IMPORTERRULES_API UIRQuerySourceFilenameEndsWith : public UIRQuerySourcePathBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	FString EndsWith;
	
	virtual bool Test_Implementation(UFactory* Factor, UObject* CreatedObject) override;
};

UCLASS(DisplayName="Source Path Contains")
class IMPORTERRULES_API UIRQuerySourcePathContains: public UIRQuerySourcePathBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	FString Contains;
	
	virtual bool Test_Implementation(UFactory* Factor, UObject* CreatedObject) override;
};

UCLASS(DisplayName="Source Extension Matches")
class IMPORTERRULES_API UIRQuerySourceExtensionMatches: public UIRQuerySourcePathBase
{
	GENERATED_BODY()
public:
	//Comma delimited list of extension to match the source file's extension with.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules")
	FString ValidExtensions;
	
	virtual bool Test_Implementation(UFactory* Factor, UObject* CreatedObject) override;
};