// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DataAsset/Item/PDA_ShopItem.h"
#include "MAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UMAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UMAssetManager& Get();

	void LoadShopItems(const FStreamableDelegate& LoadFinishedCallback);
	bool GetLoadedShopItems(TArray<const UPDA_ShopItem*>& OutItems) const;
	const FItemCollection* GetCombinationForItem(const UPDA_ShopItem* Item) const;
	const FItemCollection* GetIngredientForItem(const UPDA_ShopItem* Item) const;

private:
	void ShopItemLoadFinished(FStreamableDelegate Callback);
	void BuildItemMaps();
	void AddToCombinationMap(const UPDA_ShopItem* Ingredient, const UPDA_ShopItem* CombinationItem);

	UPROPERTY()
	TMap<const UPDA_ShopItem*, FItemCollection> CombinationMap;
	UPROPERTY()
	TMap<const UPDA_ShopItem*, FItemCollection> IngredientMap;
};
