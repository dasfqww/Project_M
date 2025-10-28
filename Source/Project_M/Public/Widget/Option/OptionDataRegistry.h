// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionDataRegistry.generated.h"

class UListDataObjectCollection;

/**
 * 
 */
UCLASS()
class PROJECT_M_API UOptionDataRegistry : public UObject
{
	GENERATED_BODY()
public:
	//Gets called by options screen right after the object of type UOptionsDataRegistry is created
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UListDataObjectCollection*>& GetRegisteredOptionsTabCollections() const { return RegisteredOptionsTabCollections; }
private:

	void CreateAndRegisterTabCollection(const FString& InID, const FString& InDisplayName);

	UPROPERTY(Transient)
	TArray<UListDataObjectCollection*> RegisteredOptionsTabCollections;
};
