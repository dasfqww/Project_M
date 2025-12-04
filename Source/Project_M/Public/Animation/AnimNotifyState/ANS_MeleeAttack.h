// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "ANS_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UANS_MeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

private:
	TArray<FHitResult> PerformTrace(USkeletalMeshComponent* MeshComp) const;

    void SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const;

	//void ProcessHitsAndSendEvent(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits);

	//void TriggerGameplayCue(const FHitResult& Hit) const;

    UPROPERTY(EditAnywhere, Category = "Trace")
    FName SocketName = "FX_Trail_01_R";

    UPROPERTY(EditAnywhere, Category = "Crash|Socket")
    float SocketExtensionOffset{ 40.f };

    UPROPERTY(EditAnywhere, Category = "Crash|Socket")
    float SphereTraceRadius{ 60.f };

    UPROPERTY(EditAnywhere, Category = "Trace")
    bool bDrawDebugs = false;

    ///* ===== A 방식 GameplayCue ===== */
    //UPROPERTY(EditAnywhere, Category = "GameplayCue")
    //TArray<FGameplayTag> CueTags;

    UPROPERTY(EditAnywhere, Category = "GameplayCue")
    FGameplayTag EventTag;

    ///* ===== A 방식 팀필터링 ===== */
    //UPROPERTY(EditAnywhere, Category = "Team")
    //TEnumAsByte<ETeamAttitude::Type> TargetTeam = ETeamAttitude::Hostile;

    ///* ===== 중복 타격 방지 ===== */
    //TSet<AActor*> HitActors;
};
