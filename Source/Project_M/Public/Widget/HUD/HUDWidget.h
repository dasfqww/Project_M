// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/GameplayAbilityType.h"
#include "HUDWidget.generated.h"

class UValueGauge;
class UAbilitySystemComponent;
class UGameplayAbility;
class UAbilityListView;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void ConfigAbilities(const  TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& InAbilities);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAbilityListView> AbilityListView;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwnerASC;
};
