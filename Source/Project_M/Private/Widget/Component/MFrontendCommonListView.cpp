// CSM All Rights Reserved.


#include "Widget/Component/MFrontendCommonListView.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widget/Option/DataListEntryMappingDataAsset.h"
#include "Widget/Option/ListDataObjectBase.h"
#include "Widget/Option/ListEntry/ListEntryWidgetBase.h"
#include "Widget/Option/DataObject/ListDataObjectCollection.h"

UUserWidget& UMFrontendCommonListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (IsDesignTime())
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}

	if (TSubclassOf<UListEntryWidgetBase> FoundWidgetClass
		= DataListEntryMapping->FindEntryWidgetClassByDataObject(CastChecked<UListDataObjectBase>(Item)))
	{
		return GenerateTypedEntry<UListEntryWidgetBase>(FoundWidgetClass, OwnerTable);
	}
	else
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);

	}
}

bool UMFrontendCommonListView::OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem)
{
	return !FirstSelectedItem->IsA<UListDataObjectCollection>();
}

#if WITH_EDITOR
void UMFrontendCommonListView::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!DataListEntryMapping)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable DataListEntryMapping has no valid data asset assigned ") +
			GetClass()->GetName() +
			TEXT(" needs a valid data asset to function properly")
		));
	}
}
#endif
