// CSM All Rights Reserved.


#include "Widget/HUD/HUDWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/MAbilitySystemComponent.h"
#include "Widget/HUD/ValueGauge.h"
#include "Widget/Ability/AbilityListView.h"
#include "GAS/MAttributeSet.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());

	/*UMAbilitySystemComponent* ASC = Cast<UMAbilitySystemComponent>(OwnerASC);
	if (IsValid(ASC))
	{
		ConfigAbilities(ASC->GetAbilities());
	}*/

	if (IsValid(OwnerASC))
	{
		HealthBar->SetAndBoundToGameplayAttribute
			(OwnerASC, UMAttributeSet::GetCurrentHealthAttribute(), UMAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBoundToGameplayAttribute
			(OwnerASC, UMAttributeSet::GetCurrentManaAttribute(), UMAttributeSet::GetMaxManaAttribute());
	}
}

void UHUDWidget::ConfigAbilities(const TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& InAbilities)
{
	AbilityListView->ConfigAbilities(InAbilities);
}
