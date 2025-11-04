// CSM All Rights Reserved.


#include "Widget/Option/DataObject/ListDataObjectValue.h"

void UListDataObjectValue::SetDataDynamicGetter(const TSharedPtr<FOptionDataInteractionHelper>& InDynamicGetter)
{
	DataDynamicGetter = InDynamicGetter;
}

void UListDataObjectValue::SetDataDynamicSetter(const TSharedPtr<FOptionDataInteractionHelper>& InDynamicSetter)
{
	DataDynamicSetter = InDynamicSetter;
}
