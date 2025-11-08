// CSM All Rights Reserved.


#include "Widget/Option/DataObject/ListDataObjectStringResolution.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widget/Option/OptionDataInteractionHelper.h"
#include "Setting/MGameUserSettings.h"

#include "MDebugHelper.h"

void UListDataObjectStringResolution::InitResolutionValues()
{
	TArray<FIntPoint> AvaialbleResolutions;

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvaialbleResolutions);

	AvaialbleResolutions.Sort(
		[](const FIntPoint& A, const FIntPoint& B)->bool
		{
			return A.SizeSquared() < B.SizeSquared();
		}
	);

	for (const FIntPoint& Resolution : AvaialbleResolutions)
	{
		AddDynamicOption(ResToValueString(Resolution), ResToDisplayText(Resolution));
	}

	MaximumAllowedResolution = ResToValueString(AvaialbleResolutions.Last());

	SetDefaultValueFromString(MaximumAllowedResolution);
}

void UListDataObjectStringResolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = ResToDisplayText(UMGameUserSettings::Get()->GetScreenResolution());
	}
}

FString UListDataObjectStringResolution::ResToValueString(const FIntPoint& InResolution) const
{
	return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UListDataObjectStringResolution::ResToDisplayText(const FIntPoint& InResolution) const
{
	const FString DisplayString = FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y);

	return FText::FromString(DisplayString);
}
