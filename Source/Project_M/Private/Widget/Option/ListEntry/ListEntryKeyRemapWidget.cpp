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

	UFrontendUISubsystem::Get(this)->PushSoftWidgetToStackAsync(
		FrontendGameplayTags::Frontend_WidgetStack_Modal,
		UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_KeyRemapScreen),
		[this](EAsyncPushWidgetState PushState, UWidget_ActivatableBase* PushedWidget)
		{
			if (PushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UKeyRemapScreenWidget* CreatedKeyRemapScreen = CastChecked<UKeyRemapScreenWidget>(PushedWidget);

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
	Debug::Print(TEXT("Reset Key Binding Button Clicked"));

}
