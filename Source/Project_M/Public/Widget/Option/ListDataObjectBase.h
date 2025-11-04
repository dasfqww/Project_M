// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Type/MFrontendEnumTypes.h"
#include "ListDataObjectBase.generated.h"

#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName;} \
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName;}

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_M_API UListDataObjectBase : public UObject
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModified, UListDataObjectBase*, EOptionsListDataModifyReason)
	FOnListDataModified OnListDataModified;

	LIST_DATA_ACCESSOR(FName, DataID)
	LIST_DATA_ACCESSOR(FText, DataDisplayName)
	LIST_DATA_ACCESSOR(FText, DescriptionRichText)
	LIST_DATA_ACCESSOR(FText, DisabledRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage)
	LIST_DATA_ACCESSOR(TObjectPtr<UListDataObjectBase>, ParentData)

	void InitDataObject();

	//Empty in the base class. Child class ListDataObject_Collection should override it. The function should return all the child data a tab has
	virtual TArray<UListDataObjectBase*> GetAllChildListData() const { return TArray<UListDataObjectBase*>(); }
	virtual bool HasAnyChildListData() const { return false; }

	void SetShouldApplySettingsImmediately(bool bShouldApplyRightAway) { bShouldApplyChangeImmediatly = bShouldApplyRightAway; }

	virtual bool HasDefaultValue() const { return false; }
	virtual bool CanResetBackToDefaultValue() const { return false; }
	virtual bool TryResetBackToDefaultValue() { return false; }

protected:
	//Empty in base class. The child classes should override it to handle the initialization needed accrodingly
	virtual void OnDataObjectInitialized();

	virtual void NotifyListDataModified(UListDataObjectBase* ModifiedData, 
		EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);

private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	TObjectPtr<UListDataObjectBase> ParentData;

	bool bShouldApplyChangeImmediatly = false;
};
