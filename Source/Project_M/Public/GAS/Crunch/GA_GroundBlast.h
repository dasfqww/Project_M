// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/MGameplayAbility.h"
#include "GA_GroundBlast.generated.h"



/**
 * 
 */
UCLASS()
class PROJECT_M_API UGA_GroundBlast : public UMGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;
};
