// CSM All Rights Reserved.


#include "Setting/MLoadingScreenSettings.h"
#include "Blueprint/UserWidget.h"


TSubclassOf<UUserWidget> UMLoadingScreenSettings::GetLoadingScreenWidgetClassChecked() const
{
    checkf(!SoftLoadingScreenWidgetClass.IsNull(), TEXT("Forgot to assign a valid widget blueprint in the project settings as loading screen"));

    TSubclassOf<UUserWidget> LoadedLoadingScreenWidget = SoftLoadingScreenWidgetClass.LoadSynchronous();

    return LoadedLoadingScreenWidget;
}
