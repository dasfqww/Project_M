// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/DataObject/ListDataObjectValue.h"
#include "ListDataObjectString.generated.h"


/**
 * 
 */
UCLASS()
class PROJECT_M_API UListDataObjectString : public UListDataObjectValue
{
	GENERATED_BODY()
public:
	void AddDynamicOption(const FString& InStringValue, const FText& InDisplayText);

	void AdvanceToNextOption();
	void BackToPreviousOption();

	void OnRotatorInitiatedValueChange(const FText& InNewSelectedText);

protected:

	virtual void OnDataObjectInitialized() override;
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;

	bool TrySetDisplayTextFromStringValue(const FString& InStringValue);

	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
public:
	FORCEINLINE const TArray<FText>& GetAvailableOptionsTextArray() const { return AvailableOptionsTextArray; }
	FORCEINLINE FText GetCurrentDisplayText() const { return CurrentDisplayText; }
};
