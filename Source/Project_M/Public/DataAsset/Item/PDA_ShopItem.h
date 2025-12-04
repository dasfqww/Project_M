// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_ShopItem.generated.h"

class UPDA_ShopItem;
USTRUCT(BlueprintType)
struct FItemCollection//추후에 다른 헤더파일로 이전해볼것
{
	GENERATED_BODY()
public:
	FItemCollection(){}
	FItemCollection(const TArray<const UPDA_ShopItem*>& InItems){}
	void AddItem(const UPDA_ShopItem* NewItem, bool bAddUnique = false){
		if (bAddUnique && Contains(NewItem)) return;
			
		Items.Add(NewItem);
	}
	FORCEINLINE bool Contains(const UPDA_ShopItem* Item) const{ return Items.Contains(Item); }
	FORCEINLINE const TArray<const UPDA_ShopItem*>& GetItems() const{ return Items; }

private:
	TArray<const UPDA_ShopItem*> Items;
};

class UTexture2D;
class UGameplayEffect;
class UGameplayAbility;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UPDA_ShopItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	static FPrimaryAssetType GetShopItemAssetType();
	
	UGameplayAbility* GetGrantedAbilityCDO() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	float Price;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	bool bIsConsumable;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSubclassOf<UGameplayEffect> EquippedEffect;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSubclassOf<UGameplayEffect> ConsumeEffect;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSubclassOf<UGameplayAbility> GrantedAbility;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	bool bIsStackable = false;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	int MaxStackCount = 5;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TArray<TSoftObjectPtr<UPDA_ShopItem>> IngredientItems;
public:
	FORCEINLINE UTexture2D* GetIcon() const { return Icon.LoadSynchronous(); }
	FORCEINLINE FText GetItemName() const { return ItemName; }
	FORCEINLINE FText GetItemDescription() const { return ItemDescription; }
	FORCEINLINE float GetPrice() const { return Price; }
	FORCEINLINE float GetSellPrice() const { return Price / 2.f; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetEquippedEffect() const { return EquippedEffect; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetConsumeEffect() const { return ConsumeEffect; }
	FORCEINLINE TSubclassOf<UGameplayAbility> GetGrantedAbility() const { return GrantedAbility; }
	FORCEINLINE bool GetIsStackable() const { return bIsStackable; }
	FORCEINLINE bool GetIsConsumable() const { return bIsConsumable; }
	FORCEINLINE int GetMaxStackCount() const { return MaxStackCount; }
	FORCEINLINE const TArray<TSoftObjectPtr<UPDA_ShopItem>>& GetIngredients() const { return IngredientItems; }

};
