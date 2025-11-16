// CSM All Rights Reserved.


#include "Widget/HUD/HUDWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Widget/HUD/ValueGauge.h"
#include "GAS/MAttributeSet.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (IsValid(OwnerASC))
	{
		HealthBar->SetAndBoundToGameplayAttribute
			(OwnerASC, UMAttributeSet::GetCurrentHealthAttribute(), UMAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBoundToGameplayAttribute
			(OwnerASC, UMAttributeSet::GetCurrentManaAttribute(), UMAttributeSet::GetMaxManaAttribute());
	}
}
