// CSM All Rights Reserved.


#include "Widget/Option/ListEntry/ListEntryWidgetString.h"
#include "Widget/Option/DataObject/ListDataObjectString.h"
#include "Widget/Component/MFrontendCommonRotator.h"
#include "Widget/Component/FrontendCommonButtonBase.h"
#include "CommonInputSubsystem.h"

#include "MDebugHelper.h"

void UListEntryWidgetString::OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningStringDataObject = CastChecked<UListDataObjectString>(InOwningListDataObject);

	AvailableOptionRotator->PopulateTextLabels(CachedOwningStringDataObject->GetAvailableOptionsTextArray());
	AvailableOptionRotator->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UListEntryWidgetString::OnOwningListDataObjectModified(UListDataObjectBase* OwningModifiedData,
	EOptionsListDataModifyReason ModifyReason)
{
	if (IsValid(CachedOwningStringDataObject))
	{
		AvailableOptionRotator->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
	}
}

void UListEntryWidgetString::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PrevOptionButton->OnClicked().AddUObject(this, &ThisClass::OnPreviousOptionButtonClicked);
	NextOptionButton->OnClicked().AddUObject(this, &ThisClass::OnNextOptionButtonClicked);

	AvailableOptionRotator->OnClicked().AddLambda([this]() {SelectThisEntryWidget(); });
	AvailableOptionRotator->OnRotatedEvent.AddUObject(this, &ThisClass::OnRotatorValueChanged);
}

void UListEntryWidgetString::OnPreviousOptionButtonClicked()
{
	//Debug::Print("prev option");

	CachedOwningStringDataObject->BackToPreviousOption();

	SelectThisEntryWidget();
}

void UListEntryWidgetString::OnNextOptionButtonClicked()
{
	//Debug::Print("next option");
	CachedOwningStringDataObject->AdvanceToNextOption();

	SelectThisEntryWidget();
}

void UListEntryWidgetString::OnRotatorValueChanged(int32 Value, bool bUserInitiated)
{
	if (!CachedOwningStringDataObject)
	{
		return;
	}

	UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

	if (!CommonInputSubsystem || !bUserInitiated)
	{
		return;
	}

	if (CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		CachedOwningStringDataObject->OnRotatorInitiatedValueChange(AvailableOptionRotator->GetSelectedText());
	}
}
