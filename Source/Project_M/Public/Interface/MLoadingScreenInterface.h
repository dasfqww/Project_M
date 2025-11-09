// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MLoadingScreenInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UMLoadingScreenInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_M_API IMLoadingScreenInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void OnLoadingScreenActivated();
	/*virtual void OnLoadingScreenActivated_Implementation();*/

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadingScreenDeactivated();
	/*virtual void OnLoadingScreenDeactivated_Implementation();*/
};
