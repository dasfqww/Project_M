// CSM All Rights Reserved.


#include "Widget/Ability/AbilityListView.h"
#include "Abilities/GameplayAbility.h"
#include "Widget/Ability/AbilityDisplayWidget.h"
#include "DataTable/AbilityWidgetDataTable.h"

void UAbilityListView::ConfigAbilities(const TMap<EMAbilityInputID, 
	TSubclassOf<UGameplayAbility>>& InAbilities)
{
	for (const TPair < EMAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : InAbilities)
	{
		AddItem(AbilityPair.Value.GetDefaultObject());
	}
}

void UAbilityListView::AbilityDisplayWidgetGenerated(UUserWidget& InWidget)
{
	UAbilityDisplayWidget* AbilityDisplayWidget = Cast<UAbilityDisplayWidget>(&InWidget);
	if (IsValid(AbilityDisplayWidget))
	{
		
	}
}

const FAbilityWidgetDataTable* UAbilityListView::
	FindAbilityWidgetData(const TSubclassOf<UGameplayAbility>& InAbilityClass)
{
	if(!IsValid(AbilityWidgetDataTable))
		return nullptr;

	for (auto& AbilityWidgetDataPair : AbilityWidgetDataTable->GetRowMap())
	{
		const FAbilityWidgetDataTable* WidgetDataTable
			= AbilityWidgetDataTable->FindRow<FAbilityWidgetDataTable>(AbilityWidgetDataPair.Key, "");
		if (WidgetDataTable->AbilityClass==InAbilityClass)
		{
			return WidgetDataTable;
		}
	}

	return nullptr;
}

