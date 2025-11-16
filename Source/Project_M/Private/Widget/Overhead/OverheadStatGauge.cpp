// CSM All Rights Reserved.


#include "Widget/Overhead/OverheadStatGauge.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Widget/HUD/ValueGauge.h"
#include "GAS/MAttributeSet.h"

void UOverheadStatGauge::ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (IsValid(AbilitySystemComponent))
	{
		HealthBar->SetAndBoundToGameplayAttribute
			(AbilitySystemComponent, 
			UMAttributeSet::GetCurrentHealthAttribute(), 
			UMAttributeSet::GetMaxHealthAttribute());
	}
}
