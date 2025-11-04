// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/ListDataObjectBase.h"
#include "ListDataObjectValue.generated.h"

class FOptionDataInteractionHelper;

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_M_API UListDataObjectValue : public UListDataObjectBase
{
	GENERATED_BODY()
public:
	void SetDataDynamicGetter(const TSharedPtr<FOptionDataInteractionHelper>& InDynamicGetter);
	void SetDataDynamicSetter(const TSharedPtr<FOptionDataInteractionHelper>& InDynamicSetter);

	virtual bool HasDefaultValue() const override { return DefaultStringValue.IsSet(); }

protected:
	FString GetDefaultValueAsString() const { return DefaultStringValue.GetValue(); }

	TSharedPtr<FOptionDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FOptionDataInteractionHelper> DataDynamicSetter;

private:
	TOptional<FString> DefaultStringValue;

public:
	FORCEINLINE void SetDefaultValueFromString(const FString& InDefaultValue) { DefaultStringValue = InDefaultValue; }
};
