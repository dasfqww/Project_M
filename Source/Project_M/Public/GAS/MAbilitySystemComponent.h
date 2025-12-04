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
	UMAbilitySystemComponent();

	void ApplyInitialEffects();
	void GiveInitialAbilities();

	const TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities()const;

	/*void AbilityInputPressed(const FGameplayTag& InputTag);
	void AbilityInputReleased(const FGameplayTag& InputTag);*/

	int32 GetInputIDFromTag(const FGameplayTag& Tag) const;

private:
	void HealthUpdated(const FOnAttributeChangeData& ChangeData);

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	/*UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> AbilityMap;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<FGameplayTag,TSubclassOf<UGameplayAbility>> BasicAbilityMap;*/
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<FGameplayTag, int32> AbilityInputTagToID;

public:

};
