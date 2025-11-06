// CSM All Rights Reserved.


#include "Widget/Option/ListEntry/ListEntryScalarWidget.h"
#include "Widget/Option/DataObject/ListDataObjectScalar.h"
#include "AnalogSlider.h"

void UListEntryScalarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SettingSlider->OnValueChanged.AddUniqueDynamic(this, &ThisClass::OnSliderValueChanged);
	SettingSlider->OnMouseCaptureBegin.AddUniqueDynamic(this, &ThisClass::OnSliderMouseCaptureBegin);
}

void UListEntryScalarWidget::OnOwningListDataObjectSet(UListDataObjectBase* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningScalarDataObject = CastChecked<UListDataObjectScalar>(InOwningListDataObject);

	SettingValueNumText->SetNumericType(CachedOwningScalarDataObject->GetDisplayNumericType());
	SettingValueNumText->FormattingSpecification = CachedOwningScalarDataObject->GetNumberFormattingOptions();
	SettingValueNumText->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue());

	SettingSlider->SetMinValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetLowerBoundValue());
	SettingSlider->SetMaxValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetUpperBoundValue());
	SettingSlider->SetStepSize(CachedOwningScalarDataObject->GetSliderStepSize());
	SettingSlider->SetValue(CachedOwningScalarDataObject->GetCurrentValue());
}

void UListEntryScalarWidget::OnOwningListDataObjectModified(UListDataObjectBase* OwningModifiedData, 
	EOptionsListDataModifyReason ModifyReason)
{
	if (IsValid(CachedOwningScalarDataObject))
	{
		SettingValueNumText->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue());
		SettingSlider->SetValue(CachedOwningScalarDataObject->GetCurrentValue());
	}
}

void UListEntryScalarWidget::OnSliderValueChanged(float Value)
{
	if (IsValid(CachedOwningScalarDataObject))
	{
		CachedOwningScalarDataObject->SetCurrentValueFromSlider(Value);
	}
}

void UListEntryScalarWidget::OnSliderMouseCaptureBegin()
{
	SelectThisEntryWidget();
}
