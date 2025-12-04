// CSM All Rights Reserved.


#include "GAS/Crunch/GA_GroundBlast.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UGA_GroundBlast::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!HasAuthorityOrPredictionKey(CurrentActorInfo, &CurrentActivationInfo))
		return;

	UAbilityTask_PlayMontageAndWait* PlayAttackAnimTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage);
	PlayAttackAnimTask->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
	PlayAttackAnimTask->OnCancelled.AddDynamic(this, &ThisClass::K2_EndAbility);
	PlayAttackAnimTask->OnInterrupted.AddDynamic(this, &ThisClass::K2_EndAbility);
	PlayAttackAnimTask->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
	PlayAttackAnimTask->ReadyForActivation();
}
