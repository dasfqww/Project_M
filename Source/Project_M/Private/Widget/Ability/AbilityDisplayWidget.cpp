// CSM All Rights Reserved.


#include "Widget/Ability/AbilityDisplayWidget.h"
#include "Components/Image.h"
#include "DataTable/AbilityWidgetDataTable.h"

void UAbilityDisplayWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}

void UAbilityDisplayWidget::ConfigWidgetData(const FAbilityWidgetDataTable* InWidgetDataTable)
{
	if (IsValid(AbilityIcon) && InWidgetDataTable)
	{
		AbilityIcon->GetDynamicMaterial()->
			SetTextureParameterValue(IconMaterialParam, InWidgetDataTable->Icon.LoadSynchronous());
	}
}
