// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_ActivatableBase.h"
#include "CommonInputTypeEnum.h"
#include "KeyRemapScreenWidget.generated.h"

class UCommonRichTextBlock;
class FKeyRemapScreenInputPreprocessor;


/**
 * 
 */
UCLASS()
class PROJECT_M_API UKeyRemapScreenWidget : public UWidget_ActivatableBase
{
	GENERATED_BODY()
public:
	void SetDesiredInputTypeToFilter(ECommonInputType InDesiredInputType);

protected:
	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~ End UCommonActivatableWidget Interface

private:
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> RemapMessageRichText;
	//***** Bound Widgets ***** //

	TSharedPtr<FKeyRemapScreenInputPreprocessor> CachedInputPreprocessor;
	ECommonInputType CachedDesiredInputType;
};
