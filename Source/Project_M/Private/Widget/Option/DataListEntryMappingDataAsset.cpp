// CSM All Rights Reserved.


#include "Widget/Option/DataListEntryMappingDataAsset.h"
#include "Widget/Option/ListDataObjectBase.h"

TSubclassOf<UListEntryWidgetBase>
UDataListEntryMappingDataAsset::FindEntryWidgetClassByDataObject(UListDataObjectBase* InDataObject) const
{
	check(InDataObject);

	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass = DataObjectClass->GetSuperClass())
	{
		if (TSubclassOf<UListDataObjectBase> ConvertedDataObjectClass 
			= TSubclassOf<UListDataObjectBase>(DataObjectClass))
		{
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}

	return TSubclassOf<UListEntryWidgetBase>();
}
