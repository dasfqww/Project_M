// CSM All Rights Reserved.


#include "DataAsset/Item/PDA_ShopItem.h"
#include "Abilities/GameplayAbility.h"

FPrimaryAssetId UPDA_ShopItem::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(GetShopItemAssetType(), GetFName());
}

FPrimaryAssetType UPDA_ShopItem::GetShopItemAssetType()
{
    return FPrimaryAssetType("ShopItem");
}

UGameplayAbility* UPDA_ShopItem::GetGrantedAbilityCDO() const
{
	if (GrantedAbility)
	{
		return Cast<UGameplayAbility>(GrantedAbility->GetDefaultObject());
	}

	return nullptr;
}
