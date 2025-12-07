// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MPlayerController.h"
#include "Character/Player/MPlayerCharacter.h"
#include "Widget/HUD/HUDWidget.h"
#include "Net/UnrealNetwork.h"

void AMPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	PlayerCharacter = Cast<AMPlayerCharacter>(NewPawn);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->ServerSideInit();
		PlayerCharacter->SetGenericTeamId(TeamID);
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

void AMPlayerController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamID = InTeamID;
}

FGenericTeamId AMPlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void AMPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMPlayerController, TeamID);
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
