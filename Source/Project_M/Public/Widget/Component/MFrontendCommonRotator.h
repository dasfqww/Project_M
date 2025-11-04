// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "MFrontendCommonRotator.generated.h"



/**
 * 
 */
UCLASS()
class PROJECT_M_API UMFrontendCommonRotator : public UCommonRotator
{
	GENERATED_BODY()
public:
	void SetSelectedOptionByText(const FText& InTextOption);
};
