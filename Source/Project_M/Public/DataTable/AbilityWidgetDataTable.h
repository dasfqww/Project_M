#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilityWidgetDataTable.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FAbilityWidgetDataTable :public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AbilityName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};