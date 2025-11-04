// CSM All Rights Reserved.


#include "Setting/MGameUserSettings.h"

UMGameUserSettings* UMGameUserSettings::Get()
{
	if (IsValid(GEngine))
	{
		return CastChecked<UMGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}
