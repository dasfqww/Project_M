// CSM All Rights Reserved.


#include "Widget/Component/MFrontendCommonRotator.h"
#include "CommonTextBlock.h"

void UMFrontendCommonRotator::SetSelectedOptionByText(const FText& InTextOption)
{
	const int32 FoundIndex = TextLabels.IndexOfByPredicate(
		[InTextOption](const FText& TextItem)->bool
		{
			return TextItem.EqualTo(InTextOption);
		}
	);

	if (FoundIndex != INDEX_NONE)
	{
		SetSelectedItem(FoundIndex);
	}
	else
	{
		MyText->SetText(InTextOption);
	}
}
