// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadStatGauge.generated.h"

class UValueGauge;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UOverheadStatGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConfigureWithASC(class UAbilitySystemComponent* AbilitySystemComponent);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
};
