// CSM All Rights Reserved.


#include "Widget/Widget_PrimaryLayOut.h"


#include "MDebugHelper.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayOut::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InTag), 
		TEXT("Can not find the widget stack by the tag %s"), *InTag.ToString());

	return RegisteredWidgetStackMap.FindRef(InTag);
}

void UWidget_PrimaryLayOut::RegisterWidgetStack(UPARAM(meta = (Categories = "Frontend.WidgetStack")) 
	FGameplayTag InStackTag,
	UCommonActivatableWidgetContainerBase* InStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);

			Debug::Print(TEXT("Widget Stack Registered under the tag ") + InStackTag.ToString());
		}
	}
}