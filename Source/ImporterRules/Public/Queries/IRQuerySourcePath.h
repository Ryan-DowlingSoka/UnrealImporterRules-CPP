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