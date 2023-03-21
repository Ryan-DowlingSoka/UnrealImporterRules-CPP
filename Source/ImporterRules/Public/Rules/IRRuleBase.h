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
#include "UObject/Object.h"
#include "Queries/IRQueryBase.h"
#include "Actions/IRActionBase.h"
#include "IRRuleBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, meta=(DisplayName="Post Import Rule Base"), AutoExpandCategories=("Importer Rules"), CollapseCategories)
class IMPORTERRULES_API UIRRuleBase : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category="Importer Rules")
	bool bApplyOnReimport;

	UFUNCTION(BlueprintNativeEvent, Category="Importer Rules")
	bool Apply(UFactory* Factory, UObject* CreatedObject);
};

UCLASS(meta=(DisplayName="Post Import Rule"))
class IMPORTERRULES_API UIRRule : public UIRRuleBase
{
	GENERATED_BODY()
public:

	virtual bool Apply_Implementation(UFactory* Factory, UObject* CreatedObject) override;
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category="Importer Rules", meta=(ExposeOnSpaw))
	TArray<TObjectPtr<UIRQueryBase>> Queries;
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category="Importer Rules", meta=(ExposeOnSpawn))
	TArray<TObjectPtr<UIRActionBase>> Actions;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Importer Rules", meta=(ExposeOnSpawn))
	bool bRequiresAll;
	
};
