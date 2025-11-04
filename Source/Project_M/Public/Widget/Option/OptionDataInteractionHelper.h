// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UMGameUserSettings;

/**
 * 
 */
class PROJECT_M_API FOptionDataInteractionHelper
{
public:
	FOptionDataInteractionHelper(const FString& InSetterOrGetterFuncPath);

	FString GetValueAsString() const;
	void SetValueFromString(const FString& InStringValue);

private:
	FCachedPropertyPath CachedDynamicFunctionPath;
	TWeakObjectPtr<UMGameUserSettings> CachedWeakGameUserSettings;
};
