// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Widget_ActivatableBase.h"
#include "MOptionScreenWidget.generated.h"

class UOptionDataRegistry;
class UMFrontendTabListWidgetBase;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class PROJECT_M_API UMOptionScreenWidget : public UWidget_ActivatableBase
{
	GENERATED_BODY()
protected:

	virtual void NativeOnInitialized() override;

private:
	virtual void NativeOnActivated() override;

	UOptionDataRegistry* GetOrCreateDataRegistry();

	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMFrontendTabListWidgetBase> OptionTabs;

	UPROPERTY(Transient)
	TObjectPtr<UOptionDataRegistry> CreatedOwningDataRegistry;

	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
