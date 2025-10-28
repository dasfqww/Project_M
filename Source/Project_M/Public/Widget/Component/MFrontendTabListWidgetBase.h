// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "MFrontendTabListWidgetBase.generated.h"

class UFrontendCommonButtonBase;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UMFrontendTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()
public:
	void RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName);

private:
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Settings", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebugEditorPreviewTabCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UFrontendCommonButtonBase> TabButtonEntryWidgetClass;
};
