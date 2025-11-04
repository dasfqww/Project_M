// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataListEntryMappingDataAsset.generated.h"

class UListDataObjectBase;
class UListEntryWidgetBase;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UDataListEntryMappingDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	TSubclassOf<UListEntryWidgetBase>
		FindEntryWidgetClassByDataObject(UListDataObjectBase* InDataObject) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TMap< TSubclassOf<UListDataObjectBase>, TSubclassOf<UListEntryWidgetBase> > DataObjectListEntryMap;
};
