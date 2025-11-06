// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/DataObject/ListDataObjectString.h"
#include "ListDataObjectStringBool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UListDataObjectStringBool : public UListDataObjectString
{
	GENERATED_BODY()
public:
	void OverrideTrueDisplayText(const FText& InNewTrueDisplayText);
	void OverrideFalseDisplayText(const FText& InNewFalseDisplayText);
	void SetTrueAsDefaultValue();
	void SetFalseAsDefaultValue();

protected:
	//~ Begin UListDataObject_String Interface
	virtual void OnDataObjectInitialized() override;
	//~ End UListDataObject_String Interface

private:
	void TryInitBoolValues();

	const FString TrueString = TEXT("true");
	const FString FalseString = TEXT("false");
};
