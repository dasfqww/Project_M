// CSM All Rights Reserved.


#include "Widget/Option/ListEntry/ListEntryKeyRemapWidget.h"
#include "Widget/Option/DataObject/ListDataObjectKeyRemap.h"
#include "Widget/Component/FrontendCommonButtonBase.h"
#include "Subsystem/FrontendUISubsystem.h"
#include "FrontendGameplayTags.h"
#include "FrontendFunctionLibrary.h"
#include "Widget/Option/KeyRemapScreenWidget.h"

#include "MDebugHelper.h"

void UListEntryKeyRemapWidget::NativeOnInitialized()
{
	RemapKeyButton->OnClicked().AddUObject(this, &ThisClass::OnRemapKeyButtonClicked);
	ResetKeyBindingButton->OnClicked().AddUObject(this, &ThisClass::OnResetKeyBindingButtonClicked);
}

void UListEntryKeyRemapWidget::OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningKeyRemapDataObject = CastChecked<UListDataObjectKeyRemap>(InOwningListDataObject);

	RemapKeyButton->SetButtionDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UListEntryKeyRemapWidget::OnOwningListDataObjectModified
	(UListDataObjectBase* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (CachedOwningKeyRemapDataObject)
	{
		RemapKeyButton->SetButtionDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
	}
}

void UListEntryKeyRemapWidget::OnRemapKeyButtonClicked()
{
	//Debug::Print(TEXT("Remap Key Button Clicked"));

	SelectThisEntryWidget();

	UFrontendUISubsystem::Get(this)->PushSoftWidgetToStackAsync(
		FrontendGameplayTags::Frontend_WidgetStack_Modal,
		UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_KeyRemapScreen),
		[this](EAsyncPushWidgetState PushState, UWidget_ActivatableBase* PushedWidget)
		{
			if (PushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UKeyRemapScreenWidget* CreatedKeyRemapScreen = CastChecked<UKeyRemapScreenWidget>(PushedWidget);
				CreatedKeyRemapScreen->OnKeyRemapScreenKeyPressed.BindUObject(this, &ThisClass::OnKeyToRemapPressed);
				CreatedKeyRemapScreen->OnKeyRemapScreenKeySelectCanceled.BindUObject(this, &ThisClass::OnKeyRemapCanceled);

				if (CachedOwningKeyRemapDataObject)
				{
					CreatedKeyRemapScreen->SetDesiredInputTypeToFilter(CachedOwningKeyRemapDataObject->GetDesiredInputKeyType());
				}
			}
		}
	);

}

void UListEntryKeyRemapWidget::OnResetKeyBindingButtonClicked()
{
	//Debug::Print(TEXT("Reset Key Binding Button Clicked"));
	SelectThisEntryWidget();

	if (!IsValid(CachedOwningKeyRemapDataObject)) return;

	//Check if the current key is already the default key. Display an OK screen that says this is already the default key to the player
	if (!CachedOwningKeyRemapDataObject->CanResetBackToDefaultValue())
	{
		UFrontendUISubsystem::Get(this)->PushConfirmScreenToModalStackAynsc(
			EConfirmScreenType::Ok,
			FText::FromString(TEXT("Reset Key Mapping")),
			FText::FromString(TEXT("The key binding for ") + CachedOwningKeyRemapDataObject->GetDataDisplayName().ToString() + TEXT(" is already set to default.")),
			[](EConfirmScreenButtonType ClickedButton) {}
		);

		return;
	}

	//Reset the key binding back to default
	UFrontendUISubsystem::Get(this)->PushConfirmScreenToModalStackAynsc(
		EConfirmScreenType::YesNo,
		FText::FromString(TEXT("Reset Key Mapping")),
		FText::FromString(TEXT("Are you sure you want to reset the key binding for ") + CachedOwningKeyRemapDataObject->GetDataDisplayName().ToString() + TEXT(" ?")),
		[this](EConfirmScreenButtonType ClickedButton)
		{
			if (ClickedButton == EConfirmScreenButtonType::Confirmed)
			{
				CachedOwningKeyRemapDataObject->TryResetBackToDefaultValue();
			}
		}
	);
}

void UListEntryKeyRemapWidget::OnKeyToRemapPressed(const FKey& PressedKey)
{
	//Debug::Print(TEXT("Valid key to remap detected. Key: ") + PressedKey.GetDisplayName().ToString());
	if (CachedOwningKeyRemapDataObject)
	{
		CachedOwningKeyRemapDataObject->BindNewInputKey(PressedKey);
	}
}

void UListEntryKeyRemapWidget::OnKeyRemapCanceled(const FString& CanceledReason)
{
	UFrontendUISubsystem::Get(this)->PushConfirmScreenToModalStackAynsc(
		EConfirmScreenType::Ok,
		FText::FromString(TEXT("Key Remap")),
		FText::FromString(CanceledReason),
		[](EConfirmScreenButtonType ClickedButton) {}
	);
}
