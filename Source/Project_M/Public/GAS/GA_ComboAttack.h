// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/MGameplayAbility.h"
#include "GA_ComboAttack.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UGA_ComboAttack : public UMGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_ComboAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;
};
