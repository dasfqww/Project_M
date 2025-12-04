// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "Type/GameplayAbilityType.h"
#include "AbilityListView.generated.h"

class UGameplayAbility;
struct FAbilityWidgetDataTable;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UAbilityListView : public UListView
{
	GENERATED_BODY()
public:
	void ConfigAbilities(const  TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& InAbilities);

private:
	UPROPERTY(EditAnywhere, Category = "Data")
	TObjectPtr<UDataTable> AbilityWidgetDataTable;
	
	void AbilityDisplayWidgetGenerated(UUserWidget& InWidget);

	const struct FAbilityWidgetDataTable* 
		FindAbilityWidgetData(const TSubclassOf<UGameplayAbility>& InAbilityClass);
};
