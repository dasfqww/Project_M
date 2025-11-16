// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Type/GameplayAbilityType.h"
#include "MAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void ApplyInitialEffects();
	void GiveInitialAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> AbilityMap;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<FGameplayTag,TSubclassOf<UGameplayAbility>> BasicAbilityMap;
};
