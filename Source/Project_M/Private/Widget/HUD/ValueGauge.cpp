// CSM All Rights Reserved.


#include "Widget/HUD/ValueGauge.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AbilitySystemComponent.h"

#include "MDebugHelper.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();

	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (IsValid(AbilitySystemComponent))
	{
		bool bFound;
		float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
		float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);
		if (bFound)
		{
			SetValue(Value, MaxValue);
		}

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGauge::ValueChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGauge::MaxValueChanged);
	}
}

void UValueGauge::SetValue(float InValue, float InMaxValue)
{
	if (InValue==0)
	{
		Debug::Print(FString::Printf(TEXT("Value Gauge: %s, InMaxValue can't be 0"), *GetName()));
		return;
	}

	float Ratio = InValue / InMaxValue;
	ProgressBar->SetPercent(Ratio);

	FNumberFormattingOptions FormatOps = FNumberFormattingOptions().SetMinimumFractionalDigits(0);

	ValueText->SetText(FText::Format(
		FTextFormat::FromString("{0}/{1}"),
		FText::AsNumber(InValue, &FormatOps),
		FText::AsNumber(InMaxValue, &FormatOps)));
}

void UValueGauge::ValueChanged(const FOnAttributeChangeData& ChangedData)
{
	SetValue(ChangedData.NewValue, CachedMaxValue);
}

void UValueGauge::MaxValueChanged(const FOnAttributeChangeData& ChangedData)
{
	SetValue(CachedValue, ChangedData.NewValue);
}
