// CSM All Rights Reserved.


#include "GAS/GA_ComboAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "MGameplayTags.h"

#include "MDebugHelper.h"

UGA_ComboAttack::UGA_ComboAttack()
{
	AbilityTags.AddTag(MGameplayTags::Ability_BasicAttack);
	BlockAbilitiesWithTag.AddTag(MGameplayTags::Ability_BasicAttack);
}

void UGA_ComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
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
	}

}
