// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Type/MFrontendEnumTypes.h"
#include "ListEntryWidgetBase.generated.h"

class UCommonTextBlock;
class UListDataObjectBase;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class PROJECT_M_API UListEntryWidgetBase : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
	
	void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnEntryReleased() override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject);

	virtual void OnOwningListDataObjectModified(UListDataObjectBase* OwningModifiedData, 
		EOptionsListDataModifyReason ModifyReason);

	void SelectThisEntryWidget();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonTextBlock> SettingDisplayNameTextBlock;
};
