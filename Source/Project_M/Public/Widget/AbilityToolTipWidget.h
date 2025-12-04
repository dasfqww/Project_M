// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityToolTipWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UAbilityToolTipWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AbilityIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DescriptionTextBlock;


};
