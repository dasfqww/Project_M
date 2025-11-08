// CSM All Rights Reserved.


#include "Widget/Option/MOptionDetailViewWidget.h"
#include "CommonTextBlock.h"
#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "Widget/Option/ListDataObjectBase.h"

void UMOptionDetailViewWidget::UpdateDetailsViewInfo(UListDataObjectBase* InDataObject,
	const FString& InEntryWidgetClassName)
{
	if (!IsValid(InDataObject)) return;

	TitleTextBlock->SetText(InDataObject->GetDataDisplayName());

	if (!InDataObject->GetSoftDescriptionImage().IsNull())
	{
		DescriptionImage->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
		DescriptionImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	DescriptionRichText->SetText(InDataObject->GetDescriptionRichText());

	const FString DynamicDetails = FString::Printf(
		TEXT("Data Object Class: <Bold>%s</>\n\nEntry Widget Class:<Bold>%s</>"),
		*InDataObject->GetClass()->GetName(),
		*InEntryWidgetClassName
	);

	DynamicDetailRichText->SetText(FText::FromString(DynamicDetails));

	DisabledReasonRichText->SetText(InDataObject->IsDataCurrentlyEditable() ? 
		FText::GetEmpty() : InDataObject->GetDisabledRichText());
}

void UMOptionDetailViewWidget::ClearDetailsViewInfo()
{
	TitleTextBlock->SetText(FText::GetEmpty());
	DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	DescriptionRichText->SetText(FText::GetEmpty());
	DynamicDetailRichText->SetText(FText::GetEmpty());
	DisabledReasonRichText->SetText(FText::GetEmpty());
}

void UMOptionDetailViewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClearDetailsViewInfo();
}
