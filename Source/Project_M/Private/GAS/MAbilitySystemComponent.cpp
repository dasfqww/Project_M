// CSM All Rights Reserved.


#include "GAS/MAbilitySystemComponent.h"

void UMAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UMAbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	for (const auto& AbilityPair : AbilityMap)
	{
		//GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, (int32)AbilityPair.Key, nullptr));
		FGameplayAbilitySpec Spec(AbilityPair.Value, 0, INDEX_NONE, this);
		Spec.DynamicAbilityTags.AddTag(AbilityPair.Key); // ← InputTag 저장
		GiveAbility(Spec);
	}
	
	for (const auto& AbilityPair : BasicAbilityMap)
	{
		//GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, (int32)AbilityPair.Key, nullptr));
		FGameplayAbilitySpec Spec(AbilityPair.Value, 1, INDEX_NONE, this);
		Spec.DynamicAbilityTags.AddTag(AbilityPair.Key); // ← InputTag 저장
		GiveAbility(Spec);
	}
}
