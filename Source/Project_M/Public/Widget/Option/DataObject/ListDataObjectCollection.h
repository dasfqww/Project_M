// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/ListDataObjectBase.h"
#include "ListDataObjectCollection.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UListDataObjectCollection : public UListDataObjectBase
{
	GENERATED_BODY()
public:
	void AddChildListData(UListDataObjectBase* InChildListData);

	//~ Begin UListDataObject_Base Interface
	virtual TArray<UListDataObjectBase*> GetAllChildListData() const;
	virtual bool HasAnyChildListData() const;
	//~ End UListDataObject_Base Interface

private:
	UPROPERTY(Transient)
	TArray<UListDataObjectBase*> ChildListDataArray;
};