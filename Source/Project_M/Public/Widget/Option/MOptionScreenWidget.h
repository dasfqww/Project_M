// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Type/MFrontendEnumTypes.h"
#include "MOptionScreenWidget.generated.h"

class UOptionDataRegistry;
class UMFrontendTabListWidgetBase;
class UMFrontendCommonListView;
class UMOptionDetailViewWidget;
class UListDataObjectBase;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class PROJECT_M_API UMOptionScreenWidget : public UWidget_ActivatableBase
{
	GENERATED_BODY()
protected:

	virtual void NativeOnInitialized() override;

private:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	UOptionDataRegistry* GetOrCreateDataRegistry();

	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);

	void OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered);
	void OnListViewItemSelected(UObject* InSelectedItem);

	FString TryGetEntryWidgetClassName(UObject* InOwningListItem) const;

	void OnListViewListDataModified(UListDataObjectBase* ModifiedData, EOptionsListDataModifyReason ModifyReason);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMFrontendTabListWidgetBase> OptionTabs;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMFrontendCommonListView> OptionList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMOptionDetailViewWidget> ListEntryInfoView;

	UPROPERTY(Transient)
	TObjectPtr<UOptionDataRegistry> CreatedOwningDataRegistry;

	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;

	UPROPERTY(Transient)
	TArray<UListDataObjectBase*> ResettableDataArray;

	bool bIsResettingData = false;
};
