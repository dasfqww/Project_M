// CSM All Rights Reserved.


#include "Widget/Option/OptionDataRegistry.h"
#include "Widget/Option/DataObject/ListDataObjectCollection.h"

void UOptionDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	CreateAndRegisterTabCollection(TEXT("GameplayTabCollection"), TEXT("Gameplay"));
	CreateAndRegisterTabCollection(TEXT("AudioTabCollection"), TEXT("Audio"));
	CreateAndRegisterTabCollection(TEXT("VideoTabCollection"), TEXT("Video"));
	CreateAndRegisterTabCollection(TEXT("ControlTabCollection"), TEXT("Control"));
}

void UOptionDataRegistry::CreateAndRegisterTabCollection(const FString& InID, const FString& InDisplayName)
{
	UListDataObjectCollection* ControlTabCollection = NewObject<UListDataObjectCollection>();

	ControlTabCollection->SetDataID(FName(InID));
	ControlTabCollection->SetDataDisplayName(FText::FromString(InDisplayName));

	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}
