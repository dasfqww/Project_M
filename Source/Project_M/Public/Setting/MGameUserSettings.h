// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "MGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UMGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	static UMGameUserSettings* Get();

	//***** Gameplay Collection Tab ***** //
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }

	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }

private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
};
