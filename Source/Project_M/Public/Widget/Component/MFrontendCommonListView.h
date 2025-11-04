// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "MFrontendCommonListView.generated.h"

class UDataListEntryMappingDataAsset;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UMFrontendCommonListView : public UCommonListView
{
	GENERATED_BODY()
protected:
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, 
		TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	virtual bool OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem) override;

private:
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

	UPROPERTY(EditAnywhere, Category = "Frontend List View Settings")
	TObjectPtr<UDataListEntryMappingDataAsset> DataListEntryMapping;
};
