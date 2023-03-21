// Fill out your copyright notice in the Description page of Project Settings.


#include "Queries/IRQueryDestinationPath.h"

bool UIRQueryDestinationPathContains::Test_Implementation(UFactory* Factor, UObject* CreatedObject)
{
	if(!IsValid(CreatedObject))
		return false;

	return CreatedObject->GetPathName().Contains(Contains, bCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase);
}
