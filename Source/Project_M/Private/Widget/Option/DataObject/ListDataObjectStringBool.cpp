// CSM All Rights Reserved.


#include "Widget/Option/DataObject/ListDataObjectStringBool.h"

void UListDataObjectStringBool::OverrideTrueDisplayText(const FText& InNewTrueDisplayText)
{
	if (!AvailableOptionsStringArray.Contains(TrueString))
	{
		AddDynamicOption(TrueString, InNewTrueDisplayText);
	}
}

void UListDataObjectStringBool::OverrideFalseDisplayText(const FText& InNewFalseDisplayText)
{
	if (!AvailableOptionsStringArray.Contains(FalseString))
	{
		AddDynamicOption(FalseString, InNewFalseDisplayText);
	}
}

void UListDataObjectStringBool::SetTrueAsDefaultValue()
{
	SetDefaultValueFromString(TrueString);
}

void UListDataObjectStringBool::SetFalseAsDefaultValue()
{
	SetDefaultValueFromString(FalseString);
}

void UListDataObjectStringBool::OnDataObjectInitialized()
{
	TryInitBoolValues();

	Super::OnDataObjectInitialized();
}

void UListDataObjectStringBool::TryInitBoolValues()
{
	if (!AvailableOptionsStringArray.Contains(TrueString))
	{
		AddDynamicOption(TrueString, FText::FromString(TEXT("ON")));
	}

	if (!AvailableOptionsStringArray.Contains(FalseString))
	{
		AddDynamicOption(FalseString, FText::FromString(TEXT("OFF")));
	}
}
