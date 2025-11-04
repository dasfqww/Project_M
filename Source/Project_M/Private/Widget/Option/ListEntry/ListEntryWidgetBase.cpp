// CSM All Rights Reserved.


#include "Widget/Option/ListEntry/ListEntryWidgetBase.h"
#include "Widget/Option/ListDataObjectBase.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "CommonInputSubsystem.h"


void UListEntryWidgetBase::NativeOnListEntryWidgetHovered(bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered, IsListItemSelected());
}

void UListEntryWidgetBase::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	//SetVisibility(ESlateVisibility::Visible);

	OnOwningListDataObjectSet(CastChecked<UListDataObjectBase>(ListItemObject));
}

void UListEntryWidgetBase::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	NativeOnListEntryWidgetHovered(false);
}

FReply UListEntryWidgetBase::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

	if (CommonInputSubsystem && CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (UWidget* WidgetToFocus = BP_GetWidgetToFocusForGamepad())
		{
			if (TSharedPtr<SWidget> SlateWidgetToFocus = WidgetToFocus->GetCachedWidget())
			{
				return FReply::Handled().SetUserFocus(SlateWidgetToFocus.ToSharedRef());
			}
		}
	}

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UListEntryWidgetBase::OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject)
{
	if (IsValid(SettingDisplayNameTextBlock))
	{
		SettingDisplayNameTextBlock->SetText(InOwningListDataObject->GetDataDisplayName());
	}

	if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InOwningListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwningListDataObjectModified);
	}
}

void UListEntryWidgetBase::OnOwningListDataObjectModified(UListDataObjectBase* OwningModifiedData, 
	EOptionsListDataModifyReason ModifyReason)
{

}

void UListEntryWidgetBase::SelectThisEntryWidget()
{
	CastChecked<UListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}
