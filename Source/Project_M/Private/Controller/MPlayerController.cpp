// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MPlayerController.h"
#include "Character/Player/MPlayerCharacter.h"
#include "Widget/HUD/HUDWidget.h"

void AMPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	PlayerCharacter = Cast<AMPlayerCharacter>(NewPawn);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->ServerSideInit();
	}

}

void AMPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);

	PlayerCharacter = Cast<AMPlayerCharacter>(NewPawn);

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->ClientSideInit();
		DisplayHUDWidget();
	}
}

void AMPlayerController::DisplayHUDWidget()
{
	if (!IsLocalPlayerController()) return;

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
		HUDWidget->ConfigAbilities(PlayerCharacter->GetAbilities());
	}
}
