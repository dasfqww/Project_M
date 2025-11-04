// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/ListEntry/ListEntryWidgetBase.h"
#include "ListEntryWidgetString.generated.h"

class UFrontendCommonButtonBase;
class UMFrontendCommonRotator;
class UListDataObjectString;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class PROJECT_M_API UListEntryWidgetString : public UListEntryWidgetBase
{
	GENERATED_BODY()
protected:
	virtual void OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UListDataObjectBase* OwningModifiedData,
		EOptionsListDataModifyReason ModifyReason);

	virtual void NativeOnInitialized() override;


private:
	void OnPreviousOptionButtonClicked();
	void OnNextOptionButtonClicked();

	void OnRotatorValueChanged(int32 Value, bool bUserInitiated);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UFrontendCommonButtonBase> PrevOptionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UMFrontendCommonRotator> AvailableOptionRotator;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UFrontendCommonButtonBase> NextOptionButton;

	UPROPERTY(Transient)
	TObjectPtr<UListDataObjectString> CachedOwningStringDataObject;
};
