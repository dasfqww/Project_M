// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/DataObject/ListDataObjectString.h"
#include "ListDataObjectStringInteger.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UListDataObjectStringInteger : public UListDataObjectString
{
	GENERATED_BODY()
public:
	void AddIntegerOption(int32 InIntegerValue, const FText& InDisplayText);

protected:
	//~ Begin UListDataObject_String Interface
	virtual void OnDataObjectInitialized() override;
	virtual void OnEditDependencyDataModified
		(UListDataObjectBase* ModifiedDependencyData, EOptionsListDataModifyReason ModifyReason) override;
	//~ End UListDataObject_String Interface
};
