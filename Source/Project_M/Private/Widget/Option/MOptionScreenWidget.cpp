// CSM All Rights Reserved.


#include "Widget/Option/MOptionScreenWidget.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "Widget/Option/OptionDataRegistry.h"
#include "Widget/Component/MFrontendTabListWidgetBase.h"
#include "Widget/Option/DataObject/ListDataObjectCollection.h"
#include "Widget/Component/MFrontendCommonListView.h"
#include "Setting/MGameUserSettings.h"
#include "Widget/Option/ListEntry/ListEntryWidgetBase.h"
#include "Widget/Option/MOptionDetailViewWidget.h"
#include "Subsystem/FrontendUISubsystem.h"
#include "Widget/Component/FrontendCommonButtonBase.h"

#include "MDebugHelper.h"

void UMOptionScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)
			)
		);
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
		)
	);

	OptionTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);

	OptionList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
	OptionList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
}

void UMOptionScreenWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (UListDataObjectCollection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection)
		{
			continue;
		}

		const FName TabID = TabCollection->GetDataID();

		if (OptionTabs->GetTabButtonBaseByID(TabID) != nullptr)
		{
			continue;
		}

		OptionTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

void UMOptionScreenWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	UMGameUserSettings::Get()->ApplySettings(true);
}

UWidget* UMOptionScreenWidget::NativeGetDesiredFocusTarget() const
{
	if (UObject* SelectedObject = OptionList->GetSelectedItem())
	{
		if (UUserWidget* SelectedEntryWidget = OptionList->GetEntryWidgetFromItem(SelectedObject))
		{
			return SelectedEntryWidget;
		}
	}

	return Super::NativeGetDesiredFocusTarget();
}

UOptionDataRegistry* UMOptionScreenWidget::GetOrCreateDataRegistry()
{
	if (!CreatedOwningDataRegistry)
	{
		CreatedOwningDataRegistry = NewObject<UOptionDataRegistry>();
		CreatedOwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}

	checkf(CreatedOwningDataRegistry, TEXT("Data registry for options screen is not valid"));

	return CreatedOwningDataRegistry;
}

void UMOptionScreenWidget::OnResetBoundActionTriggered()
{
	//Debug::Print("Reset bound action triggered");
	if (ResettableDataArray.IsEmpty()) return;

	UCommonButtonBase* SelectedTabButton = OptionTabs->GetTabButtonBaseByID(OptionTabs->GetActiveTab());

	const FString SelectedTabButtonName = CastChecked<UFrontendCommonButtonBase>(SelectedTabButton)->GetButtonDisplayText().ToString();

	UFrontendUISubsystem::Get(this)->PushConfirmScreenToModalStackAynsc(
		EConfirmScreenType::YesNo,
		FText::FromString(TEXT("Reset")),
		FText::FromString(TEXT("Are you sure you want to reset all the settings under the ") + SelectedTabButtonName + TEXT(" tab?")),
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			if (ClickedButtonType != EConfirmScreenButtonType::Confirmed)
			{
				return;
			}

			bIsResettingData = true;
			bool bHasDataFailedToReset = false;

			for (UListDataObjectBase* DataToReset : ResettableDataArray)
			{
				if (!DataToReset)
				{
					continue;
				}

				if (DataToReset->TryResetBackToDefaultValue())
				{
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" was reset"));
				}
				else
				{
					bHasDataFailedToReset = true;
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" failed to reset"));
				}
			}

			if (!bHasDataFailedToReset)
			{
				ResettableDataArray.Empty();
				RemoveActionBinding(ResetActionHandle);
			}

			bIsResettingData = false;
		}
	);
}

void UMOptionScreenWidget::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void UMOptionScreenWidget::OnOptionsTabSelected(FName TabId)
{
	//Debug::Print(TEXT("New Tab Selected. Tab ID: ") + TabId.ToString());
	ListEntryInfoView->ClearDetailsViewInfo();

	TArray<UListDataObjectBase*> FoundListSourceItems 
		= GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);

	OptionList->SetListItems(FoundListSourceItems);
	OptionList->RequestRefresh();

	if (OptionList->GetNumItems() != 0)
	{
		OptionList->NavigateToIndex(0);
		OptionList->SetSelectedIndex(0);
	}

	ResettableDataArray.Empty();

	for (UListDataObjectBase* FoundListSourceItem : FoundListSourceItems)
	{
		if (!FoundListSourceItem)
		{
			continue;
		}

		if (!FoundListSourceItem->OnListDataModified.IsBoundToObject(this))
		{
			FoundListSourceItem->OnListDataModified.AddUObject(this, &ThisClass::OnListViewListDataModified);
		}

		if (FoundListSourceItem->CanResetBackToDefaultValue())
		{
			ResettableDataArray.AddUnique(FoundListSourceItem);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
	else
	{
		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
}

void UMOptionScreenWidget::OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered)
{
	if (!IsValid(InHoveredItem)) return;

	UListEntryWidgetBase* HoveredEntryWidget
		= OptionList->GetEntryWidgetFromItem<UListEntryWidgetBase>(InHoveredItem);

	check(HoveredEntryWidget);
	
	HoveredEntryWidget->NativeOnListEntryWidgetHovered(bWasHovered);

	if (bWasHovered)
	{
		ListEntryInfoView->UpdateDetailsViewInfo(
			CastChecked<UListDataObjectBase>(InHoveredItem),
			TryGetEntryWidgetClassName(InHoveredItem)
		);
	}
	else
	{
		if (UListDataObjectBase* SelectedItem = OptionList->GetSelectedItem<UListDataObjectBase>())
		{
			ListEntryInfoView->UpdateDetailsViewInfo(
				SelectedItem,
				TryGetEntryWidgetClassName(SelectedItem)
			);
		}
	}
}

void UMOptionScreenWidget::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!IsValid(InSelectedItem)) return;

	ListEntryInfoView->UpdateDetailsViewInfo(
		CastChecked<UListDataObjectBase>(InSelectedItem),
		TryGetEntryWidgetClassName(InSelectedItem)
	);
}

FString UMOptionScreenWidget::TryGetEntryWidgetClassName(UObject* InOwningListItem) const
{
	return FString();
}

void UMOptionScreenWidget::OnListViewListDataModified(UListDataObjectBase* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (!ModifiedData || bIsResettingData) return;
	

	if (ModifiedData->CanResetBackToDefaultValue())
	{
		ResettableDataArray.AddUnique(ModifiedData);

		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
	else
	{
		if (ResettableDataArray.Contains(ModifiedData))
		{
			ResettableDataArray.Remove(ModifiedData);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
}
