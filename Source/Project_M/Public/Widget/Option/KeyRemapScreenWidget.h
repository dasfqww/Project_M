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

	DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeyPressedDelegate, const FKey& /*PressedKey*/)
	FOnKeyRemapScreenKeyPressedDelegate OnKeyRemapScreenKeyPressed;

	DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeySelectCanceledDelegate, const FString& /*CanceledReason*/)
	FOnKeyRemapScreenKeySelectCanceledDelegate OnKeyRemapScreenKeySelectCanceled;

protected:
	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~ End UCommonActivatableWidget Interface

private:
	void OnValidKeyPressedDetected(const FKey& PressedKey);
	void OnKeySelectCanceled(const FString& CanceledReason);

	//Delay a tick to make sure the input key is captured properly before calling the PreDeactivateCallback and deactivating the widget
	void RequestDeactivateWidget(TFunction<void()> PreDeactivateCallback);

	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> RemapMessageRichText;
	//***** Bound Widgets ***** //

	TSharedPtr<FKeyRemapScreenInputPreprocessor> CachedInputPreprocessor;
	ECommonInputType CachedDesiredInputType;
};
