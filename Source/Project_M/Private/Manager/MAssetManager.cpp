// CSM All Rights Reserved.


#include "Manager/MAssetManager.h"

#include "MDebugHelper.h"

UMAssetManager& UMAssetManager::Get()
{
	UMAssetManager* Singleton = Cast<UMAssetManager>(GEngine->AssetManager.Get());
	if (Singleton)
	{
		return *Singleton;
	}

	//UE_LOG(LogLoad, Fatal, TEXT("Asset Manager Needs to be of the type CAssetMaanger"));
	Debug::PrintFatalError("Asset Manager Needs to be of the type CAssetMaanger");
	return (*NewObject<UMAssetManager>());
}

void UMAssetManager::LoadShopItems(const FStreamableDelegate& LoadFinishedCallback)
{
	LoadPrimaryAssetsWithType(UPDA_ShopItem::GetShopItemAssetType(),
		TArray<FName>(), FStreamableDelegate::CreateUObject(this, 
			&UMAssetManager::ShopItemLoadFinished, LoadFinishedCallback));
}

bool UMAssetManager::GetLoadedShopItems(TArray<const UPDA_ShopItem*>& OutItems) const
{
	TArray<UObject*> LoadedObjects;
	bool bLoaded = GetPrimaryAssetObjectList(UPDA_ShopItem::GetShopItemAssetType(), LoadedObjects);

	if (bLoaded)
	{
		for (UObject* ObjectLoaded : LoadedObjects)
		{
			OutItems.Add(Cast<UPDA_ShopItem>(ObjectLoaded));
		}
	}

	return bLoaded;
}

const FItemCollection* UMAssetManager::GetCombinationForItem(const UPDA_ShopItem* Item) const
{
	return nullptr;
}

const FItemCollection* UMAssetManager::GetIngredientForItem(const UPDA_ShopItem* Item) const
{
	return nullptr;
}

void UMAssetManager::ShopItemLoadFinished(FStreamableDelegate Callback)
{
	Callback.ExecuteIfBound();
	BuildItemMaps();
}

void UMAssetManager::BuildItemMaps()
{
	TArray<const UPDA_ShopItem*> LoadedItems;
	if (GetLoadedShopItems(LoadedItems))
	{
		for (const UPDA_ShopItem* Item : LoadedItems)
		{
			if (Item->GetIngredients().Num() == 0)
			{
				continue;
			}

			TArray<const UPDA_ShopItem*> Items;
			for (const TSoftObjectPtr<UPDA_ShopItem>& Ingredient : Item->GetIngredients())
			{
				UPDA_ShopItem* IngredientItem = Ingredient.LoadSynchronous();
				Items.Add(IngredientItem);
				AddToCombinationMap(IngredientItem, Item);
			}

			IngredientMap.Add(Item, FItemCollection{ Items });
		}
	}
}

void UMAssetManager::AddToCombinationMap(const UPDA_ShopItem* Ingredient, const UPDA_ShopItem* CombinationItem)
{
	FItemCollection* Combinations = CombinationMap.Find(Ingredient);
	if (Combinations)
	{
		if (!Combinations->Contains(CombinationItem))
			Combinations->AddItem(CombinationItem);
	}
	else
	{
		CombinationMap.Add(Ingredient, FItemCollection{ TArray<const UPDA_ShopItem*>{CombinationItem} });
	}
}
