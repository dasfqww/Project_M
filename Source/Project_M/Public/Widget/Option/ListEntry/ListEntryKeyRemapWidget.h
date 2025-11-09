// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/ListEntry/ListEntryWidgetBase.h"
#include "ListEntryKeyRemapWidget.generated.h"

class UFrontendCommonButtonBase;
class UListDataObjectKeyRemap;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UListEntryKeyRemapWidget : public UListEntryWidgetBase
{
	GENERATED_BODY()
protected:

	virtual void NativeOnInitialized() override;

	//~ Begin UWidget_ListEntry_Base Interface
	virtual void OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified
		(UListDataObjectBase* OwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;
	//~ End UWidget_ListEntry_Base Interface

private:
	void OnRemapKeyButtonClicked();
	void OnResetKeyBindingButtonClicked();

	void OnKeyToRemapPressed(const FKey& PressedKey);
	void OnKeyRemapCanceled(const FString& CanceledReason);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UFrontendCommonButtonBase> RemapKeyButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UFrontendCommonButtonBase> ResetKeyBindingButton;

	UPROPERTY(Transient)
	TObjectPtr<UListDataObjectKeyRemap> CachedOwningKeyRemapDataObject;
};
