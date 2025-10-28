// CSM All Rights Reserved.


#include "Widget/Option/DataObject/ListDataObjectCollection.h"

void UListDataObjectCollection::AddChildListData(UListDataObjectBase* InChildListData)
{
	//Notify the child list data to init itself
	InChildListData->InitDataObject();

	//Set the child list data's parent to this
	InChildListData->SetParentData(this);

	ChildListDataArray.Add(InChildListData);
}

TArray<UListDataObjectBase*> UListDataObjectCollection::GetAllChildListData() const
{
	return ChildListDataArray;
}

bool UListDataObjectCollection::HasAnyChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}
