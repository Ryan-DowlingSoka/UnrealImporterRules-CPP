// Fill out your copyright notice in the Description page of Project Settings.


#include "Rules/IRRuleBase.h"

bool UIRRuleBase::Apply_Implementation(UFactory* Factory, UObject* CreatedObject)
{
	return false;
}

bool UIRRule::Apply_Implementation(UFactory* Factory, UObject* CreatedObject)
{
	bool bPassesTests = bRequiresAll || (Queries.Num() == 0);

	for (const TObjectPtr<UIRQueryBase> Query : Queries)
	{
		if (bRequiresAll)
		{
			bPassesTests = bPassesTests && Query->Test(Factory, CreatedObject);
			if (!bPassesTests) break;
		}
		else
		{
			bPassesTests = bPassesTests || Query->Test(Factory, CreatedObject);
			if (bPassesTests) break;
		}
	}

	if(!bPassesTests) return false;
	
	bool bAllActionsSucceeded = true;
	for (const TObjectPtr<UIRActionBase> Action : Actions)
	{
		bAllActionsSucceeded = bAllActionsSucceeded && Action->Apply(Factory, CreatedObject);
	}

	return bAllActionsSucceeded;
}
