// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MGameplayAbility.generated.h"

class UAnimInstance;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

protected:
	UAnimInstance* GetOwnerAnimInstance() const;

	TArray<FHitResult> GetHitResultFromSweepLocationTargetData(
		const FGameplayAbilityTargetDataHandle& TargetDataHandle, 
		float SphereSweepRadius = 30.f,  bool bDrawDebug = false, bool bIgnoreSelf = true) const;

};
