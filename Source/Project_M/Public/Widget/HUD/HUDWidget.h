// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UValueGauge;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwnerASC;
};
