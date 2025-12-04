// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Type/GameplayAbilityType.h"
#include "AbilityDisplayWidget.generated.h"

class UImage;
class UTextBlock;
struct FAbilityWidgetDataTable;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UAbilityDisplayWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void ConfigWidgetData(const FAbilityWidgetDataTable* InWidgetDataTable);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName IconMaterialParam = "Icon";

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AbilityIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownCounterText;

	/*UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownDurationText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CostText;*/
};
