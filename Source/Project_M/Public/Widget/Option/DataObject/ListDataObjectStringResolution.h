// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Option/DataObject/ListDataObjectString.h"
#include "ListDataObjectStringResolution.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UListDataObjectStringResolution : public UListDataObjectString
{
	GENERATED_BODY()
public:
	void InitResolutionValues();

protected:
	//~ Begin UListDataObject_String Interface
	virtual void OnDataObjectInitialized() override;
	//~ End UListDataObject_String Interface

private:
	FString ResToValueString(const FIntPoint& InResolution) const;
	FText ResToDisplayText(const FIntPoint& InResolution) const;

	FString MaximumAllowedResolution;

public:
	FORCEINLINE FString GetMaximumAllowedResolution() const { return MaximumAllowedResolution; }
};
