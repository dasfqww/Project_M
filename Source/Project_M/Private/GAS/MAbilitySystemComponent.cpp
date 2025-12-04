// CSM All Rights Reserved.


#include "GAS/MAbilitySystemComponent.h"
#include "GAS/MAttributeSet.h"

UMAbilitySystemComponent::UMAbilitySystemComponent()
{

}

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

	for (const TPair<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, (int32)AbilityPair.Key, nullptr));
	}

	for (const TPair<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, (int32)AbilityPair.Key, nullptr));
	}

	//for (const auto& AbilityPair : AbilityMap)
	//{
	//	//GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, (int32)AbilityPair.Key, nullptr));
	//	FGameplayAbilitySpec Spec(AbilityPair.Value, 0, INDEX_NONE, this);
	//	Spec.DynamicAbilityTags.AddTag(AbilityPair.Key); // ← InputTag 저장
	//	GiveAbility(Spec);
	//}
	//
	//for (const auto& AbilityPair : BasicAbilityMap)
	//{
	//	//GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, (int32)AbilityPair.Key, nullptr));
	//	FGameplayAbilitySpec Spec(AbilityPair.Value, 1, INDEX_NONE, this);
	//	Spec.DynamicAbilityTags.AddTag(AbilityPair.Key); // ← InputTag 저장
	//	GiveAbility(Spec);
	//}
}

const TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& UMAbilitySystemComponent::GetAbilities() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return Abilities;
}

//void UMAbilitySystemComponent::AbilityInputPressed(const FGameplayTag& InputTag)
//{
//	if (!InputTag.IsValid()) return;
//
//	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
//	{
//		TryActivateAbility(AbilitySpec.Handle);
//	}
//
//	//const int32 InputID = AbilityInputTagToID.FindRef(InputTag);
//	//AbilityLocalInputPressed(InputID);
//}
//
//void UMAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
//{
//	if (!InputTag.IsValid()) return;
//
//	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
//	{
//		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
//		{
//			CancelAbilityHandle(AbilitySpec.Handle);
//		}
//	}
//
//	//const int32 InputID = AbilityInputTagToID.FindRef(InputTag);
//	//AbilityLocalInputReleased(InputID);
//}

int32 UMAbilitySystemComponent::GetInputIDFromTag(const FGameplayTag& Tag) const
{
	/*const int32* FoundID = AbilityInputTagToID.Find(Tag);

	
	
	return FoundID;
	*/
	return 0;
}

void UMAbilitySystemComponent::HealthUpdated(const FOnAttributeChangeData& ChangeData)
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	if (ChangeData.NewValue<=0&&IsValid(DeathEffectClass))
	{
		FGameplayEffectSpecHandle EffectSpecHandle 
			= MakeOutgoingSpec(DeathEffectClass, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}


