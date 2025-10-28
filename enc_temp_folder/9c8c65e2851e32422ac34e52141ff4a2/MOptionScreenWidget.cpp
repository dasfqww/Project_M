// CSM All Rights Reserved.


#include "Widget/Option/MOptionScreenWidget.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "Widget/Option/OptionDataRegistry.h"
#include "Widget/Component/MFrontendTabListWidgetBase.h"
#include "Widget/Option/DataObject/ListDataObjectCollection.h"

#include "MDebugHelper.h"

void UMOptionScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)
			)
		);
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
		)
	);
}

void UMOptionScreenWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (UListDataObjectCollection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection)
		{
			continue;
		}

		const FName TabID = TabCollection->GetDataID();

		if (OptionTabs->GetTabButtonBaseByID(TabID) != nullptr)
		{
			continue;
		}

		OptionTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

UOptionDataRegistry* UMOptionScreenWidget::GetOrCreateDataRegistry()
{
	if (!CreatedOwningDataRegistry)
	{
		CreatedOwningDataRegistry = NewObject<UOptionDataRegistry>();
		CreatedOwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}

	checkf(CreatedOwningDataRegistry, TEXT("Data registry for options screen is not valid"));

	return CreatedOwningDataRegistry;
}

void UMOptionScreenWidget::OnResetBoundActionTriggered()
{
	Debug::Print("Reset bound action triggered");
}

void UMOptionScreenWidget::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}
