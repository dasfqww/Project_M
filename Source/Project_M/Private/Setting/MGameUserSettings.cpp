// CSM All Rights Reserved.


#include "Setting/MGameUserSettings.h"

UMGameUserSettings::UMGameUserSettings()
	:OverallVolume(1.f),
	MusicVolume(1.f),
	SFXVolume(1.f),
	bAllowBackgroundAudio(false),
	bUseHDRAudioMode(false)
{

}

UMGameUserSettings* UMGameUserSettings::Get()
{
	if (IsValid(GEngine))
	{
		return CastChecked<UMGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}

void UMGameUserSettings::SetOverallVolume(float InVolume)
{
	OverallVolume = InVolume;
}

void UMGameUserSettings::SetMusicVolume(float InVolume)
{
	MusicVolume = InVolume;
}

void UMGameUserSettings::SetSoundFXVolume(float InVolume)
{
	SFXVolume = InVolume;
}

void UMGameUserSettings::SetAllowBackgroundAudio(bool bIsAllowed)
{
	bAllowBackgroundAudio = bIsAllowed;
}

void UMGameUserSettings::SetUseHDRAudioMode(bool bIsAllowed)
{
	bUseHDRAudioMode = bIsAllowed;
}

float UMGameUserSettings::GetCurrentDisplayGamma() const
{
	if (GEngine)
	{
		return GEngine->GetDisplayGamma();
	}

	return 0.0f;
}

void UMGameUserSettings::SetCurrentDisplayGamma(float InNewGamma)
{
	if (GEngine)
	{
		GEngine->DisplayGamma = InNewGamma;
	}
}
