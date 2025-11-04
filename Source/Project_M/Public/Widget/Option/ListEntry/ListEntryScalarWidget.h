// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/ListEntry/ListEntryWidgetBase.h"
#include "ListEntryScalarWidget.generated.h"

class UCommonNumericTextBlock;
class UAnalogSlider;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class PROJECT_M_API UListEntryScalarWidget : public UListEntryWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UListDataObjectBase* OwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonNumericTextBlock> SettingValueNumText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UAnalogSlider> SettingSlider;
};
