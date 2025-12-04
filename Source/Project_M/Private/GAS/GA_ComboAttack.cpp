// CSM All Rights Reserved.


#include "GAS/GA_ComboAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MGameplayTags.h"

#include "MDebugHelper.h"

UGA_ComboAttack::UGA_ComboAttack()
{
	AbilityTags.AddTag(MGameplayTags::Ability_BasicAttack);
	BlockAbilitiesWithTag.AddTag(MGameplayTags::Ability_BasicAttack);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_ComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}

	//Debug::Print("Casting GA combo");
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayAttackMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage);
		PlayAttackMontageTask->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAttackMontageTask->OnCancelled.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAttackMontageTask->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAttackMontageTask->OnInterrupted.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAttackMontageTask->ReadyForActivation();

		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask
			= UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
				this, GetComboChangedEventTag(), nullptr, false, false);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &ThisClass::ComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
	}

	if (K2_HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* WaitTargetingEventTask
			= UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetComboTargetEventTag());
		WaitTargetingEventTask->EventReceived.AddDynamic(this, &ThisClass::DoDamage);
		WaitTargetingEventTask->ReadyForActivation();
	}

	NextComboName = NAME_None;
	SetupWaitComboInputPress();
	//ryCommitCombo(NextComboName);
}

FGameplayTag UGA_ComboAttack::GetComboChangedEventTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Change");
}

FGameplayTag UGA_ComboAttack::GetComboChangedEventEndTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Change.End");
}

FGameplayTag UGA_ComboAttack::GetComboTargetEventTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Damage");
}

void UGA_ComboAttack::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPress->OnPress.AddDynamic(this, &ThisClass::HandleInputPress);
	WaitInputPress->ReadyForActivation();
}

void UGA_ComboAttack::HandleInputPress(float TimeWaited)
{
	SetupWaitComboInputPress();
	TryCommitCombo();
}

TSubclassOf<UGameplayEffect> UGA_ComboAttack::GetDamageEffectForCurrentCombo() const
{
	UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if (OwnerAnimInstance)
	{
		FName CurrentSectionName = OwnerAnimInstance->Montage_GetCurrentSection(AttackMontage);
		const TSubclassOf<UGameplayEffect>* FoundEffectPtr = DamageEffectMap.Find(CurrentSectionName);
		if (FoundEffectPtr)
		{
			return *FoundEffectPtr;
		}
	}

	return DefaultDamageEffect;
}

void UGA_ComboAttack::DoDamage(FGameplayEventData Data)
{
	TArray<FHitResult> HitResults = GetHitResultFromSweepLocationTargetData(Data.TargetData, 30.f, true, true);

	Debug::Print("Do Damage..");

	for (const FHitResult& HitResult : HitResults)
	{
		TSubclassOf<UGameplayEffect> GameplayEffect = GetDamageEffectForCurrentCombo();
		FGameplayEffectSpecHandle EffectSpecHandle = 
			MakeOutgoingGameplayEffectSpec(GameplayEffect, 
				GetAbilityLevel(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()));

		ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(),
			CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle,
			UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor()));
	}
}

void UGA_ComboAttack::TryCommitCombo()
{
	if (NextComboName == NAME_None)
	{
		return;
	}

	UAnimInstance* OwnerAnimInst = GetOwnerAnimInstance();
	if (!OwnerAnimInst)
	{
		return;
	}

	OwnerAnimInst->Montage_SetNextSection(
		OwnerAnimInst->Montage_GetCurrentSection(AttackMontage), NextComboName, AttackMontage);
}

void UGA_ComboAttack::ComboChangedEventReceived(FGameplayEventData Data)
{
	FGameplayTag EventTag = Data.EventTag;

	if (EventTag == GetComboChangedEventEndTag())
	{
		NextComboName = NAME_None;
		Debug::Print(TEXT("Next combo is cleared"));
		return;
	}

	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	NextComboName = TagNames.Last();

	//TryCommitCombo(NextComboName);

	Debug::Print(FString::Printf(TEXT("Next combo is now : %s"), *NextComboName.ToString()));
}
