// CSM All Rights Reserved.


#include "Widget/Option/OptionDataInteractionHelper.h"
#include "Setting/MGameUserSettings.h"

FOptionDataInteractionHelper::FOptionDataInteractionHelper(const FString& InSetterOrGetterFuncPath)
	:CachedDynamicFunctionPath(InSetterOrGetterFuncPath)
{
	CachedWeakGameUserSettings = UMGameUserSettings::Get();
}

FString FOptionDataInteractionHelper::GetValueAsString() const
{
	FString OutStringValue;
	PropertyPathHelpers::GetPropertyValueAsString(
		CachedWeakGameUserSettings.Get(),
		CachedDynamicFunctionPath,
		OutStringValue
	);

	return OutStringValue;
}

void FOptionDataInteractionHelper::SetValueFromString(const FString& InStringValue)
{
	PropertyPathHelpers::SetPropertyValueFromString(
		CachedWeakGameUserSettings.Get(),
		CachedDynamicFunctionPath,
		InStringValue
	);
}
