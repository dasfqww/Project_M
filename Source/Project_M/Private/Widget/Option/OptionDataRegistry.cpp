// CSM All Rights Reserved.


#include "Widget/Option/OptionDataRegistry.h"
#include "Widget/Option/DataObject/ListDataObjectCollection.h"
#include "Widget/Option/DataObject/ListDataObjectString.h"
#include "Widget/Option/OptionDataInteractionHelper.h"
#include "Setting/MGameUserSettings.h"
#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Widget/Option/DataObject/ListDataObjectScalar.h"
#include "Widget/Option/DataObject/ListDataObjectStringBool.h"
#include "Widget/Option/DataObject/ListDataObjectStringEnum.h"
#include "Widget/Option/DataObject/ListDataObjectStringResolution.h"
#include "Widget/Option/DataObject/ListDataObjectStringInteger.h"
#include "Internationalization/StringTableRegistry.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Widget/Option/DataObject/ListDataObjectKeyRemap.h"

#include "MDebugHelper.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName) \
	MakeShared<FOptionDataInteractionHelper>\
		(GET_FUNCTION_NAME_STRING_CHECKED(UMGameUserSettings,SetterOrGetterFuncName))

#define GET_DESCRIPTION(InKey) \
	LOCTABLE("/Game/Blueprint/Widget/StringTable/ST_OptionScreenDescription.ST_OptionScreenDescription", InKey)

void UOptionDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab(InOwningLocalPlayer);
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
			OverallVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallVolume));
			OverallVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallVolume));
			OverallVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(OverallVolume);
		}

		//Music Volume
		{
			UListDataObjectScalar* MusicVolume = NewObject<UListDataObjectScalar>();
			MusicVolume->SetDataID(FName("MusicVolume"));
			MusicVolume->SetDataDisplayName(FText::FromString(TEXT("Music Volume")));
			MusicVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for Music Volume")));
			MusicVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			MusicVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			MusicVolume->SetSliderStepSize(0.01f);
			MusicVolume->SetDefaultValueFromString(LexToString(1.f));
			MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			MusicVolume->SetNumberFormattingOptions(UListDataObjectScalar::NoDecimal());  //No Decimal: 50%  //One Decimal: 50.5%
			MusicVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetMusicVolume));
			MusicVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetMusicVolume));
			MusicVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(MusicVolume);
		}

		//Sound FX Volume
		{
			UListDataObjectScalar* SFXVolume = NewObject<UListDataObjectScalar>();
			SFXVolume->SetDataID(FName("SoundFXVolume"));
			SFXVolume->SetDataDisplayName(FText::FromString(TEXT("Sound Effects Volume")));
			SFXVolume->SetDescriptionRichText(FText::FromString(TEXT("This is description for Sound Effects Volume")));
			SFXVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			SFXVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			SFXVolume->SetSliderStepSize(0.01f);
			SFXVolume->SetDefaultValueFromString(LexToString(1.f));
			SFXVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			SFXVolume->SetNumberFormattingOptions(UListDataObjectScalar::NoDecimal());  //No Decimal: 50%  //One Decimal: 50.5%
			SFXVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetSoundFXVolume));
			SFXVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetSoundFXVolume));
			SFXVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(SFXVolume);
		}

		//Sound Category
		{
			UListDataObjectCollection* SoundCategoryCollection = NewObject<UListDataObjectCollection>();
			SoundCategoryCollection->SetDataID(FName("SoundCategoryCollection"));
			SoundCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Sound")));

			AudioTabCollection->AddChildListData(SoundCategoryCollection);

			//Allow Background Audio
			{
				UListDataObjectStringBool* AllowBackgroundAudio = NewObject<UListDataObjectStringBool>();
				AllowBackgroundAudio->SetDataID(FName("AllowBackgroundAudio"));
				AllowBackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("Allow Background Audio")));
				AllowBackgroundAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
				AllowBackgroundAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
				AllowBackgroundAudio->SetFalseAsDefaultValue();
				AllowBackgroundAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAllowBackgroundAudio));
				AllowBackgroundAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAllowBackgroundAudio));
				AllowBackgroundAudio->SetShouldApplySettingsImmediately(true);

				SoundCategoryCollection->AddChildListData(AllowBackgroundAudio);
			}

			//Use HDR Audio
			{
				UListDataObjectStringBool* UseHDRAudioMode = NewObject<UListDataObjectStringBool>();
				UseHDRAudioMode->SetDataID(FName("UseHDRAudioMode"));
				UseHDRAudioMode->SetDataDisplayName(FText::FromString(TEXT("Use HDR Audio Mode")));
				UseHDRAudioMode->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
				UseHDRAudioMode->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
				UseHDRAudioMode->SetFalseAsDefaultValue();
				UseHDRAudioMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetUseHDRAudioMode));
				UseHDRAudioMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetUseHDRAudioMode));
				UseHDRAudioMode->SetShouldApplySettingsImmediately(true);

				SoundCategoryCollection->AddChildListData(UseHDRAudioMode);
			}
		}
	}

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionDataRegistry::InitVideoCollectionTab()
{
	UListDataObjectCollection* VideoTabCollection = NewObject<UListDataObjectCollection>();
	VideoTabCollection->SetDataID(FName("VideoTabCollection"));
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

	UListDataObjectStringEnum* CreatedWindowMode = nullptr;

	//Display Category
	{
		UListDataObjectCollection* DisplayCategoryCollection = NewObject<UListDataObjectCollection>();
		DisplayCategoryCollection->SetDataID(FName("DisplayCategoryCollection"));
		DisplayCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Display")));

		VideoTabCollection->AddChildListData(DisplayCategoryCollection);

		FOptionsDataEditConditionDescriptor PackagedBuildOnlyCondition;
		PackagedBuildOnlyCondition.SetEditConditionFunc(
			[]()->bool
			{
				const bool bIsInEditor = GIsEditor || GIsPlayInEditorWorld;

				return !bIsInEditor;
			}
		);
		PackagedBuildOnlyCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>This setting can only be adjusted in a packaged build.</>"));

		//Window Mode
		{
			UListDataObjectStringEnum* WindowMode = NewObject<UListDataObjectStringEnum>();
			WindowMode->SetDataID(FName("WindowMode"));
			WindowMode->SetDataDisplayName(FText::FromString(TEXT("Window Mode")));
			WindowMode->SetDescriptionRichText(GET_DESCRIPTION("WindowModeDescKey"));
			WindowMode->AddEnumOption(EWindowMode::Fullscreen, FText::FromString(TEXT("Fullscreen Mode")));
			WindowMode->AddEnumOption(EWindowMode::WindowedFullscreen, FText::FromString(TEXT("Borderless Window")));
			WindowMode->AddEnumOption(EWindowMode::Windowed, FText::FromString(TEXT("Windowed")));
			WindowMode->SetDefaultValueFromEnumOption(EWindowMode::WindowedFullscreen);
			WindowMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFullscreenMode));
			WindowMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFullscreenMode));
			WindowMode->SetShouldApplySettingsImmediately(true);

			WindowMode->AddEditCondition(PackagedBuildOnlyCondition);

			CreatedWindowMode = WindowMode;

			DisplayCategoryCollection->AddChildListData(WindowMode);
		}

		//Screen Resolution
		{
			UListDataObjectStringResolution* ScreenResolution = NewObject<UListDataObjectStringResolution>();
			ScreenResolution->SetDataID(FName("ScreenResolution"));
			ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("Screen Resolution")));
			ScreenResolution->SetDescriptionRichText(GET_DESCRIPTION("ScreenResolutionsDescKey"));
			ScreenResolution->InitResolutionValues();
			ScreenResolution->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetScreenResolution));
			ScreenResolution->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetScreenResolution));
			ScreenResolution->SetShouldApplySettingsImmediately(true);

			ScreenResolution->AddEditCondition(PackagedBuildOnlyCondition);

			FOptionsDataEditConditionDescriptor WindowModeEditCondition;
			WindowModeEditCondition.SetEditConditionFunc(
				[CreatedWindowMode]()->bool
				{
					const bool bIsBoderlessWindow = CreatedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::WindowedFullscreen;

					return !bIsBoderlessWindow;
				}
			);
			WindowModeEditCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>Screen Resolution is not adjustable when the 'Window Mode' is set to Borderless Window.The value must match with the maximum allowed resolution.</>"));
			WindowModeEditCondition.SetDisabledForcedStringValue(ScreenResolution->GetMaximumAllowedResolution());

			ScreenResolution->AddEditCondition(WindowModeEditCondition);

			ScreenResolution->AddEditDependencyData(CreatedWindowMode);

			DisplayCategoryCollection->AddChildListData(ScreenResolution);
		}

		//Graphics Category
		{
			UListDataObjectCollection* GraphicsCategoryCollection = NewObject<UListDataObjectCollection>();
			GraphicsCategoryCollection->SetDataID(FName("GraphicsCategoryCollection"));
			GraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Graphics")));

			VideoTabCollection->AddChildListData(GraphicsCategoryCollection);

			//Display Gamma
			{
				UListDataObjectScalar* DisplayGamma = NewObject<UListDataObjectScalar>();
				DisplayGamma->SetDataID(FName("DisplayGamma"));
				DisplayGamma->SetDataDisplayName(FText::FromString(TEXT("Brightness")));
				DisplayGamma->SetDescriptionRichText(GET_DESCRIPTION("DisplayGammaDescKey"));
				DisplayGamma->SetDisplayValueRange(TRange<float>(0.f, 1.f));
				DisplayGamma->SetOutputValueRange(TRange<float>(1.7f, 2.7f)); //The default value Unreal has is: 2.2f
				DisplayGamma->SetSliderStepSize(0.01f);
				DisplayGamma->SetDisplayNumericType(ECommonNumericType::Percentage);
				DisplayGamma->SetNumberFormattingOptions(UListDataObjectScalar::NoDecimal());
				DisplayGamma->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentDisplayGamma));
				DisplayGamma->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentDisplayGamma));
				DisplayGamma->SetDefaultValueFromString(LexToString(2.2f));

				GraphicsCategoryCollection->AddChildListData(DisplayGamma);
			}

			UListDataObjectStringInteger* CreatedOverallQuality = nullptr;

			//Overall Quality
			{
				UListDataObjectStringInteger* OverallQuality = NewObject<UListDataObjectStringInteger>();
				OverallQuality->SetDataID(FName("OverallQuality"));
				OverallQuality->SetDataDisplayName(FText::FromString(TEXT("Overall Quality")));
				OverallQuality->SetDescriptionRichText(GET_DESCRIPTION("OverallQualityDescKey"));
				OverallQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				OverallQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				OverallQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				OverallQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				OverallQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				OverallQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallScalabilityLevel));
				OverallQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallScalabilityLevel));
				OverallQuality->SetShouldApplySettingsImmediately(true);

				GraphicsCategoryCollection->AddChildListData(OverallQuality);

				CreatedOverallQuality = OverallQuality;
			}

			//Resolution Scale
			{
				UListDataObjectScalar* ResolutionScale = NewObject<UListDataObjectScalar>();
				ResolutionScale->SetDataID(FName("ResolutionScale"));
				ResolutionScale->SetDataDisplayName(FText::FromString(TEXT("3D Resolution")));
				ResolutionScale->SetDescriptionRichText(GET_DESCRIPTION("ResolutionScaleDescKey"));
				ResolutionScale->SetDisplayValueRange(TRange<float>(0.f, 1.f));
				ResolutionScale->SetOutputValueRange(TRange<float>(0.f, 1.f));
				ResolutionScale->SetSliderStepSize(0.01f);
				ResolutionScale->SetDisplayNumericType(ECommonNumericType::Percentage);
				ResolutionScale->SetNumberFormattingOptions(UListDataObjectScalar::NoDecimal());
				ResolutionScale->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetResolutionScaleNormalized));
				ResolutionScale->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetResolutionScaleNormalized));
				ResolutionScale->SetShouldApplySettingsImmediately(true);

				ResolutionScale->AddEditDependencyData(CreatedOverallQuality);

				GraphicsCategoryCollection->AddChildListData(ResolutionScale);
			}

			//Global Illumination Quality
			{
				UListDataObjectStringInteger* GlobalIlluminationQuality = NewObject<UListDataObjectStringInteger>();
				GlobalIlluminationQuality->SetDataID(FName("GlobalIlluminationQuality"));
				GlobalIlluminationQuality->SetDataDisplayName(FText::FromString(TEXT("Global Illumination")));
				GlobalIlluminationQuality->SetDescriptionRichText(GET_DESCRIPTION("GlobalIlluminationQualityDescKey"));
				GlobalIlluminationQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				GlobalIlluminationQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				GlobalIlluminationQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				GlobalIlluminationQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				GlobalIlluminationQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				GlobalIlluminationQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetGlobalIlluminationQuality));
				GlobalIlluminationQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetGlobalIlluminationQuality));
				GlobalIlluminationQuality->SetShouldApplySettingsImmediately(true);

				GlobalIlluminationQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(GlobalIlluminationQuality);

				GraphicsCategoryCollection->AddChildListData(GlobalIlluminationQuality);
			}

			//Shadow Quality
			{
				UListDataObjectStringInteger* ShadowQuality = NewObject<UListDataObjectStringInteger>();
				ShadowQuality->SetDataID(FName("ShadowQuality"));
				ShadowQuality->SetDataDisplayName(FText::FromString(TEXT("Shadow Quality")));
				ShadowQuality->SetDescriptionRichText(GET_DESCRIPTION("ShadowQualityDescKey"));
				ShadowQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				ShadowQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				ShadowQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				ShadowQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				ShadowQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				ShadowQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetShadowQuality));
				ShadowQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetShadowQuality));
				ShadowQuality->SetShouldApplySettingsImmediately(true);

				ShadowQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(ShadowQuality);

				GraphicsCategoryCollection->AddChildListData(ShadowQuality);
			}

			//AntiAliasing Quality
			{
				UListDataObjectStringInteger* AntiAliasingQuality = NewObject<UListDataObjectStringInteger>();
				AntiAliasingQuality->SetDataID(FName("AntiAliasingQuality"));
				AntiAliasingQuality->SetDataDisplayName(FText::FromString(TEXT("Anti Aliasing")));
				AntiAliasingQuality->SetDescriptionRichText(GET_DESCRIPTION("AntiAliasingDescKey"));
				AntiAliasingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				AntiAliasingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				AntiAliasingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				AntiAliasingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				AntiAliasingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				AntiAliasingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAntiAliasingQuality));
				AntiAliasingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAntiAliasingQuality));
				AntiAliasingQuality->SetShouldApplySettingsImmediately(true);

				AntiAliasingQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(AntiAliasingQuality);

				GraphicsCategoryCollection->AddChildListData(AntiAliasingQuality);
			}

			//View Distance Quality
			{
				UListDataObjectStringInteger* ViewDistanceQuality = NewObject<UListDataObjectStringInteger>();
				ViewDistanceQuality->SetDataID(FName("ViewDistanceQuality"));
				ViewDistanceQuality->SetDataDisplayName(FText::FromString(TEXT("View Distance")));
				ViewDistanceQuality->SetDescriptionRichText(GET_DESCRIPTION("ViewDistanceDescKey"));
				ViewDistanceQuality->AddIntegerOption(0, FText::FromString(TEXT("Near")));
				ViewDistanceQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				ViewDistanceQuality->AddIntegerOption(2, FText::FromString(TEXT("Far")));
				ViewDistanceQuality->AddIntegerOption(3, FText::FromString(TEXT("Very Far")));
				ViewDistanceQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				ViewDistanceQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetViewDistanceQuality));
				ViewDistanceQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetViewDistanceQuality));
				ViewDistanceQuality->SetShouldApplySettingsImmediately(true);

				ViewDistanceQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(ViewDistanceQuality);

				GraphicsCategoryCollection->AddChildListData(ViewDistanceQuality);
			}

			//Texture Quality
			{
				UListDataObjectStringInteger* TextureQuality = NewObject<UListDataObjectStringInteger>();
				TextureQuality->SetDataID(FName("TextureQuality"));
				TextureQuality->SetDataDisplayName(FText::FromString(TEXT("Texture Quality")));
				TextureQuality->SetDescriptionRichText(GET_DESCRIPTION("TextureQualityDescKey"));
				TextureQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				TextureQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				TextureQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				TextureQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				TextureQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				TextureQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetTextureQuality));
				TextureQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetTextureQuality));
				TextureQuality->SetShouldApplySettingsImmediately(true);

				TextureQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(TextureQuality);

				GraphicsCategoryCollection->AddChildListData(TextureQuality);
			}

			//Visual Effects Quality
			{
				UListDataObjectStringInteger* VisualEffectQuality = NewObject<UListDataObjectStringInteger>();
				VisualEffectQuality->SetDataID(FName("VisualEffectQuality"));
				VisualEffectQuality->SetDataDisplayName(FText::FromString(TEXT("Visual Effect Quality")));
				VisualEffectQuality->SetDescriptionRichText(GET_DESCRIPTION("VisualEffectQualityDescKey"));
				VisualEffectQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				VisualEffectQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				VisualEffectQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				VisualEffectQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				VisualEffectQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				VisualEffectQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetVisualEffectQuality));
				VisualEffectQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVisualEffectQuality));
				VisualEffectQuality->SetShouldApplySettingsImmediately(true);

				VisualEffectQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(VisualEffectQuality);

				GraphicsCategoryCollection->AddChildListData(VisualEffectQuality);
			}

			//Reflection Quality
			{
				UListDataObjectStringInteger* ReflectionQuality = NewObject<UListDataObjectStringInteger>();
				ReflectionQuality->SetDataID(FName("ReflectionQuality"));
				ReflectionQuality->SetDataDisplayName(FText::FromString(TEXT("Reflection Quality")));
				ReflectionQuality->SetDescriptionRichText(GET_DESCRIPTION("ReflectionQualityDescKey"));
				ReflectionQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				ReflectionQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				ReflectionQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				ReflectionQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				ReflectionQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				ReflectionQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetReflectionQuality));
				ReflectionQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetReflectionQuality));
				ReflectionQuality->SetShouldApplySettingsImmediately(true);

				ReflectionQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(ReflectionQuality);

				GraphicsCategoryCollection->AddChildListData(ReflectionQuality);
			}

			//Post Processing Quality
			{
				UListDataObjectStringInteger* PostProcessingQuality = NewObject<UListDataObjectStringInteger>();
				PostProcessingQuality->SetDataID(FName("PostProcessingQuality"));
				PostProcessingQuality->SetDataDisplayName(FText::FromString(TEXT("Post Processing Quality")));
				PostProcessingQuality->SetDescriptionRichText(GET_DESCRIPTION("PostProcessingQualityDescKey"));
				PostProcessingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
				PostProcessingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
				PostProcessingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
				PostProcessingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
				PostProcessingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
				PostProcessingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetPostProcessingQuality));
				PostProcessingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetPostProcessingQuality));
				PostProcessingQuality->SetShouldApplySettingsImmediately(true);

				PostProcessingQuality->AddEditDependencyData(CreatedOverallQuality);

				CreatedOverallQuality->AddEditDependencyData(PostProcessingQuality);

				GraphicsCategoryCollection->AddChildListData(PostProcessingQuality);
			}
		}

		//Advanced Graphics Category
		{
			UListDataObjectCollection* AdvancedGraphicsCategoryCollection = NewObject<UListDataObjectCollection>();
			AdvancedGraphicsCategoryCollection->SetDataID(FName("AdvancedGraphicsCategoryCollection"));
			AdvancedGraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Advanced Graphics")));

			VideoTabCollection->AddChildListData(AdvancedGraphicsCategoryCollection);

			//Vertical Sync
			{
				UListDataObjectStringBool* VerticalSync = NewObject<UListDataObjectStringBool>();
				VerticalSync->SetDataID(FName("VerticalSync"));
				VerticalSync->SetDataDisplayName(FText::FromString(TEXT("V-Sync")));
				VerticalSync->SetDescriptionRichText(GET_DESCRIPTION("VerticalSyncDescKey"));
				VerticalSync->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(IsVSyncEnabled));
				VerticalSync->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVSyncEnabled));
				VerticalSync->SetFalseAsDefaultValue();
				VerticalSync->SetShouldApplySettingsImmediately(true);

				FOptionsDataEditConditionDescriptor FullscreenOnlyCondition;
				FullscreenOnlyCondition.SetEditConditionFunc(
					[CreatedWindowMode]()->bool
					{
						return CreatedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::Fullscreen;
					}
				);
				FullscreenOnlyCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>This feature only works if the 'Window Mode' is set to 'Fullscreen'.</>"));
				FullscreenOnlyCondition.SetDisabledForcedStringValue(TEXT("false"));

				VerticalSync->AddEditCondition(FullscreenOnlyCondition);

				AdvancedGraphicsCategoryCollection->AddChildListData(VerticalSync);
			}

			//Frame Rate Limit
			{
				UListDataObjectString* FrameRateLimit = NewObject<UListDataObjectString>();
				FrameRateLimit->SetDataID(FName("FrameRateLimit"));
				FrameRateLimit->SetDataDisplayName(FText::FromString(TEXT("Frame Rate Limit")));
				FrameRateLimit->SetDescriptionRichText(GET_DESCRIPTION("FrameRateLimitDescKey"));
				FrameRateLimit->AddDynamicOption(LexToString(30.f), FText::FromString(TEXT("30 FPS")));
				FrameRateLimit->AddDynamicOption(LexToString(60.f), FText::FromString(TEXT("60 FPS")));
				FrameRateLimit->AddDynamicOption(LexToString(90.f), FText::FromString(TEXT("90 FPS")));
				FrameRateLimit->AddDynamicOption(LexToString(120.f), FText::FromString(TEXT("120 FPS")));
				FrameRateLimit->AddDynamicOption(LexToString(0.f), FText::FromString(TEXT("No Limit")));
				FrameRateLimit->SetDefaultValueFromString(LexToString(0.f));
				FrameRateLimit->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFrameRateLimit));
				FrameRateLimit->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFrameRateLimit));
				FrameRateLimit->SetShouldApplySettingsImmediately(true);

				AdvancedGraphicsCategoryCollection->AddChildListData(FrameRateLimit);
			}
		}
	}

	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionDataRegistry::InitControlCollectionTab(ULocalPlayer* InOwningLocalPlayer)
{
	UListDataObjectCollection* ControlTabCollection = NewObject<UListDataObjectCollection>();
	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));

	UEnhancedInputLocalPlayerSubsystem* EISubsystem = InOwningLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(EISubsystem);

	UEnhancedInputUserSettings* EIUserSettings = EISubsystem->GetUserSettings();

	check(EIUserSettings);

	//Keyboard Mouse Category
	{
		UListDataObjectCollection* KeyboardMouseCategoryCollection = NewObject<UListDataObjectCollection>();
		KeyboardMouseCategoryCollection->SetDataID(FName("KeyboardMouseCategoryCollection"));
		KeyboardMouseCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Keyboard & Mouse")));

		ControlTabCollection->AddChildListData(KeyboardMouseCategoryCollection);

		//Keyboard mouse inputs
		{
			FPlayerMappableKeyQueryOptions KeyboardMouseOnly;
			KeyboardMouseOnly.KeyToMatch = EKeys::S;
			KeyboardMouseOnly.bMatchBasicKeyTypes = true;

			/*FPlayerMappableKeyQueryOptions GamepadOnly;
			GamepadOnly.KeyToMatch = EKeys::Gamepad_FaceButton_Bottom;
			GamepadOnly.bMatchBasicKeyTypes = true;*/

			for (const TPair<FGameplayTag, UEnhancedPlayerMappableKeyProfile*>& ProfilePair : EIUserSettings->GetAllSavedKeyProfiles())
			{
				UEnhancedPlayerMappableKeyProfile* MappableKeyProfile = ProfilePair.Value;

				check(MappableKeyProfile);

				for (const TPair<FName, FKeyMappingRow>& MappingRowPair : MappableKeyProfile->GetPlayerMappingRows())
				{
					for (const FPlayerKeyMapping& KeyMapping : MappingRowPair.Value.Mappings)
					{
						if (MappableKeyProfile->DoesMappingPassQueryOptions(KeyMapping, KeyboardMouseOnly))
						{
							/*Debug::Print(
								TEXT(" Mapping ID: ") + KeyMapping.GetMappingName().ToString() +
								TEXT(" Display Name: ") + KeyMapping.GetDisplayName().ToString() +
								TEXT(" Bound Key: ") + KeyMapping.GetCurrentKey().GetDisplayName().ToString()
							);*/

							UListDataObjectKeyRemap* KeyRemapDataObject = NewObject<UListDataObjectKeyRemap>();
							KeyRemapDataObject->SetDataID(KeyMapping.GetMappingName());
							KeyRemapDataObject->SetDataDisplayName(KeyMapping.GetDisplayName());
							KeyRemapDataObject->InitKeyRemapData(EIUserSettings, MappableKeyProfile, ECommonInputType::MouseAndKeyboard, KeyMapping);

							KeyboardMouseCategoryCollection->AddChildListData(KeyRemapDataObject);
						}
					}
				}
			}
		}
	}

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
