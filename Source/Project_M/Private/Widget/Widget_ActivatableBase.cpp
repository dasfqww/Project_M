// CSM All Rights Reserved.


#include "Widget/Widget_ActivatableBase.h"
#include "Controller/FrontendPlayerController.h"

AFrontendPlayerController* UWidget_ActivatableBase::GetOwningFrontendPlayerController()
{
	if (!CachedOwningFrontendPC.IsValid())
	{
		//여기가 문제여서 컴파일안됨. 헤더추가해서 해당문제 해결.
		CachedOwningFrontendPC = GetOwningPlayer<AFrontendPlayerController>();
	}

	return CachedOwningFrontendPC.IsValid() ? CachedOwningFrontendPC.Get() : nullptr;
}
