// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPlayerController.generated.h"

class AMPlayerCharacter;
class UHUDWidget;

/**
 * 
 */
UCLASS()
class PROJECT_M_API AMPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// only called on the server
	void OnPossess(APawn* NewPawn) override;

	// only called on the client, also on the linstening server.
	void AcknowledgePossession(APawn* NewPawn) override;

private:
	void DisplayHUDWidget();

	UPROPERTY()
	AMPlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UHUDWidget> HUDWidget;
};
