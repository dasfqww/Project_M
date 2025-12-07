// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"


AMGameMode::AMGameMode()
{
}

APlayerController* AMGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	APlayerController* PlayerController = Super::SpawnPlayerController(InRemoteRole, Options);
	IGenericTeamAgentInterface* PlayerTeamInterface = Cast<IGenericTeamAgentInterface>(PlayerController);
	FGenericTeamId TeamID = GetTeamIDForPlayer(PlayerController);
	if (PlayerTeamInterface)
	{
		PlayerTeamInterface->SetGenericTeamId();
	}

	PlayerController->StartSpot = FindNextStartSpotForTeam();
}

FGenericTeamId AMGameMode::GetTeamIDForPlayer(const AController* InController) const
{
	static int PlayerCount = 0;
	++PlayerCount;
	return FGenericTeamId(PlayerCount % 2);
}

AActor* AMGameMode::FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const
{
	const FName* StartSpotTag = TeamStartSpotTagMap.Find(TeamID);
	if (!StartSpotTag)
	{
		return nullptr;
	}

	UWorld* World = GetWorld();

	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		if (It->PlayerStartTag == *StartSpotTag)
		{
			It->PlayerStartTag = FName("Taken");
			return *It;
		}
	}

	return nullptr;
}
