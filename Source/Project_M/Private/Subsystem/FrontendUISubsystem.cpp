// CSM All Rights Reserved.


#include "Subsystem/FrontendUISubsystem.h"
#include "Engine/AssetManager.h"
#include "Widget/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widget/Widget_ActivatableBase.h"
#include "Widget/MConfirmScreenWidget.h"
#include "FrontendGameplayTags.h"
#include "FrontendFunctionLibrary.h"

#include "MDebugHelper.h"

UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UFrontendUISubsystem>(World->GetGameInstance());
	}


	return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

void UFrontendUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayOut* InCreatedWidget)
{
	check(InCreatedWidget);

	CreatedPrimaryLayout = InCreatedWidget;

	//Debug::Print(TEXT("Primary layout widget stored"));
}

void UFrontendUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, 
	TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AysncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass, this, InWidgetStackTag, AysncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();

				check(LoadedWidgetClass && CreatedPrimaryLayout);

				UCommonActivatableWidgetContainerBase* FoundWidgetStack = 
					CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);

				UWidget_ActivatableBase* CreatedWidget = 
					FoundWidgetStack->AddWidget<UWidget_ActivatableBase>(
					LoadedWidgetClass,
					[AysncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, 
							&CreatedWidgetInstance);
					}
				);

				AysncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			}
		)
	);
}

void UFrontendUISubsystem::PushConfirmScreenToModalStackAynsc(EConfirmScreenType InScreenType, 
	const FText& InScreenTitle, const FText& InScreenMsg,
	TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;

	switch (InScreenType)
	{
	case EConfirmScreenType::Ok:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::YesNo:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::OKCancel:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::Unknown:
		break;
	default:
		break;
	}

	check(CreatedInfoObject);

	PushSoftWidgetToStackAsync(
		FrontendGameplayTags::Frontend_WidgetStack_Modal,
		UFrontendFunctionLibrary::
		GetFrontendSoftWidgetClassByTag(FrontendGameplayTags::Frontend_Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, 
			UWidget_ActivatableBase* PushedWidget)
		{
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UMConfirmScreenWidget* CreatedConfirmScreen = 
					CastChecked<UMConfirmScreenWidget>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
	);
}
