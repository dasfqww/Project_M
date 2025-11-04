// CSM All Rights Reserved.


#include "Widget/Option/OptionDataRegistry.h"
#include "Widget/Option/DataObject/ListDataObjectCollection.h"
#include "Widget/Option/DataObject/ListDataObjectString.h"
#include "Widget/Option/OptionDataInteractionHelper.h"
#include "Setting/MGameUserSettings.h"
#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Widget/Option/DataObject/ListDataObjectScalar.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName) \
	MakeShared<FOptionDataInteractionHelper>\
		(GET_FUNCTION_NAME_STRING_CHECKED(UMGameUserSettings,SetterOrGetterFuncName))

void UOptionDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
	/*CreateAndRegisterTabCollection(TEXT("GameplayTabCollection"), TEXT("Gameplay"));
	CreateAndRegisterTabCollection(TEXT("AudioTabCollection"), TEXT("Audio"));
	CreateAndRegisterTabCollection(TEXT("VideoTabCollection"), TEXT("Video"));
	CreateAndRegisterTabCollection(TEXT("ControlTabCollection"), TEXT("Control"));*/
}

TArray<UListDataObjectBase*> UOptionDataRegistry::GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const
{
	UListDataObjectCollection* const* FoundTabCollectionPtr 
		= RegisteredOptionsTabCollections.FindByPredicate(
		[InSelectedTabID](UListDataObjectCollection* AvailableTabCollection)->bool
		{
			return AvailableTabCollection->GetDataID() == InSelectedTabID;
		}
	);

	checkf(FoundTabCollectionPtr, TEXT("No valid tab found under the ID %s"), *InSelectedTabID.ToString());

	UListDataObjectCollection* FoundTabCollection = *FoundTabCollectionPtr;

	TArray<UListDataObjectBase*> AllChildListItems;

	for (UListDataObjectBase* ChildListData : FoundTabCollection->GetAllChildListData())
	{
		if (!ChildListData)
		{
			continue;
		}

		AllChildListItems.Add(ChildListData);

		if (ChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(ChildListData, AllChildListItems);
		}
	}

	return AllChildListItems;
}

void UOptionDataRegistry::FindChildListDataRecursively(UListDataObjectBase* InParentData, TArray<UListDataObjectBase*>& OutFoundChildListData) const
{
	if (!InParentData || !InParentData->HasAnyChildListData())
	{
		return;
	}

	for (UListDataObjectBase* SubChildListData : InParentData->GetAllChildListData())
	{
		if (!SubChildListData)
		{
			continue;
		}

		OutFoundChildListData.Add(SubChildListData);

		if (SubChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(SubChildListData, OutFoundChildListData);
		}
	}
}

void UOptionDataRegistry::InitGameplayCollectionTab()
{
	UListDataObjectCollection* GameplayTabCollection = NewObject<UListDataObjectCollection>();
	GameplayTabCollection->SetDataID(FName("GameplayTabCollection"));
	GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));

	//This is the full code for constructing data interactor helper
	/*TSharedPtr<FOptionDataInteractionHelper> ConstructedHelper =
	MakeShared<FOptionDataInteractionHelper>(
		GET_FUNCTION_NAME_STRING_CHECKED(UMGameUserSettings,GetCurrentGameDifficulty)
	);*/

	//TODO:Implement optiondata by a DT

	//Game Difficulty
	{
		UListDataObjectString* GameDifficulty = NewObject<UListDataObjectString>();
		GameDifficulty->SetDataID(FName("GameDifficulty"));
		GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("Difficulty")));
		GameDifficulty->SetDescriptionRichText(FText::FromString(TEXT("Adjusts the difficulty of the game experience.\n\n<Bold>Easy:</> Focuses on the story experience. Provides the most relaxing combat.\n\n<Bold>Normal:</> Offers slightly harder combat experience\n\n<Bold>Hard:</> Offers a much more challenging combat experience\n\n<Bold>Vert Hard:</> Provides the most challenging combat experience. Not recommended for first play through.")));
		GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("Easy")));
		GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("Normal")));
		GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("Hard")));
		GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("Very Hard")));
		GameDifficulty->SetDefaultValueFromString(TEXT("Normal"));
		GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentGameDifficulty));
		GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentGameDifficulty));
		GameDifficulty->SetShouldApplySettingsImmediately(true);

		GameplayTabCollection->AddChildListData(GameDifficulty);
	}

	//Test Item
	{
		UListDataObjectString* TestItem = NewObject<UListDataObjectString>();
		TestItem->SetDataID(FName("TestItem"));
		TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Image Item")));
		TestItem->SetSoftDescriptionImage(UFrontendFunctionLibrary::GetOptionsSoftImageByTag(FrontendGameplayTags::Frontend_Image_TestImage));
		TestItem->SetDescriptionRichText(FText::FromString(TEXT("The image to display can be specified in the project settings. It can be anything the developer assigned in there")));

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionDataRegistry::InitAudioCollectionTab()
{
	UListDataObjectCollection* AudioTabCollection = NewObject<UListDataObjectCollection>();
	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

	//Volume Category
	{
		UListDataObjectCollection* VolumeCategoryCollection = NewObject<UListDataObjectCollection>();
		VolumeCategoryCollection->SetDataID(FName("VolumeCategoryCollection"));
		VolumeCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Volume")));

		AudioTabCollection->AddChildListData(VolumeCategoryCollection);

		//overall volume
		{
			UListDataObjectScalar* OverallVolume = NewObject<UListDataObjectScalar>();
			OverallVolume->SetDataID(FName("OverallVolume"));
			OverallVolume->SetDataDisplayName(FText::FromString(TEXT("Overall Volume")));
			OverallVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for Overall Volume")));
			OverallVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			OverallVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			OverallVolume->SetSliderStepSize(0.01f);
			OverallVolume->SetDefaultValueFromString(LexToString(1.f));
			OverallVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			OverallVolume->SetNumberFormattingOptions(UListDataObjectScalar::NoDecimal());  //No Decimal: 50%  //One Decimal: 50.5%
			//TODO:: Set data dynamic getter and setter for the data object

			VolumeCategoryCollection->AddChildListData(OverallVolume);
		}
	}

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionDataRegistry::InitVideoCollectionTab()
{
	UListDataObjectCollection* VideoTabCollection = NewObject<UListDataObjectCollection>();
	VideoTabCollection->SetDataID(FName("VideoTabCollection"));
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionDataRegistry::InitControlCollectionTab()
{
	UListDataObjectCollection* ControlTabCollection = NewObject<UListDataObjectCollection>();
	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));

	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}

//void UOptionDataRegistry::CreateAndRegisterTabCollection(const FString& InID, const FString& InDisplayName)
//{
//	UListDataObjectCollection* ControlTabCollection = NewObject<UListDataObjectCollection>();
//
//	ControlTabCollection->SetDataID(FName(InID));
//	ControlTabCollection->SetDataDisplayName(FText::FromString(InDisplayName));
//
//	RegisteredOptionsTabCollections.Add(ControlTabCollection);
//}
