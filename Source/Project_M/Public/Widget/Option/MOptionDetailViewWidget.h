// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MOptionDetailViewWidget.generated.h"

class UCommonTextBlock;
class UCommonLazyImage;
class UCommonRichTextBlock;
class UListDataObjectBase;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class PROJECT_M_API UMOptionDetailViewWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateDetailsViewInfo(UListDataObjectBase* InDataObject, 
		const FString& InEntryWidgetClassName = FString());
	void ClearDetailsViewInfo();

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonLazyImage> DescriptionImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> DescriptionRichText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> DynamicDetailRichText;	

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> DisabledReasonRichText;
};
