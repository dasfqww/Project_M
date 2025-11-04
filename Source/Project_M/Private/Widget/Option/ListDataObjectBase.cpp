// CSM All Rights Reserved.


#include "Widget/Option/ListDataObjectBase.h"
#include "Setting/MGameUserSettings.h"

void UListDataObjectBase::InitDataObject()
{
	OnDataObjectInitialized();
}

void UListDataObjectBase::OnDataObjectInitialized()
{
	if (bShouldApplyChangeImmediatly)
	{
		UMGameUserSettings::Get()->ApplySettings(true);
	}
}

void UListDataObjectBase::NotifyListDataModified(UListDataObjectBase* ModifiedData, 
	EOptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedData, ModifyReason);
}
