// CSM All Rights Reserved.


#include "Animation/AnimNotifyState/ANS_MeleeAttack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "GAS/MAbilitySystemComponent.h"
#include "KismetTraceUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Character/Player/MPlayerCharacter.h"
#include "GameplayCueManager.h"
#include "DrawDebugHelpers.h"

void UANS_MeleeAttack::NotifyTick(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

    if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner()))
        return;

    // 1) 충돌 감지 (B 방식)
    TArray<FHitResult> Hits = PerformTrace(MeshComp);

    SendEventsToActors(MeshComp, Hits);

    // 2) A 방식 로직 전체 수행
    //ProcessHitsAndSendEvent(MeshComp, Hits);
}

TArray<FHitResult> UANS_MeleeAttack::PerformTrace(USkeletalMeshComponent* MeshComp) const
{
    TArray<FHitResult> OutHits;

    const FTransform SocketTransform = MeshComp->GetSocketTransform(SocketName);
    const FVector Start = SocketTransform.GetLocation();
    const FVector ExtendedSocketDirection =
        UKismetMathLibrary::GetForwardVector(SocketTransform.GetRotation().Rotator()) * SocketExtensionOffset;
    const FVector End = Start + ExtendedSocketDirection;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(MeshComp->GetOwner());
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	UWorld* World = GEngine->GetWorldFromContextObject(MeshComp, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World)) return OutHits;

	bool const bHit = World->SweepMultiByChannel(
		OutHits,
		Start,
		End,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(SphereTraceRadius),
		Params,
		ResponseParams);

	if (bDrawDebugs)
	{
		DrawDebugSphereTraceMulti(
			World,
			Start,
			End,
			SphereTraceRadius,
			EDrawDebugTrace::ForDuration,
			bHit,
			OutHits,
			FColor::Red,
			FColor::Green,
			5.f);
	}

	return OutHits;
}

void UANS_MeleeAttack::SendEventsToActors(USkeletalMeshComponent* MeshComp, 
    const TArray<FHitResult>& Hits) const
{
	for (const FHitResult& Hit : Hits)
	{
		AMCharacter* Character = Cast<AMCharacter>(Hit.GetActor());
		if (!IsValid(Character)) continue;
		//if (!PlayerCharacter->IsAlive()) continue;
		UMAbilitySystemComponent* ASC = Character->GetMAbilitySystemComponent();
		if (!IsValid(ASC)) continue;

		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddHitResult(Hit);

		FGameplayEventData Payload;
		Payload.Target = Character;
		Payload.ContextHandle = ContextHandle;
		Payload.Instigator = MeshComp->GetOwner();

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, Payload);
	}
}

//void UANS_MeleeAttack::ProcessHitsAndSendEvent(USkeletalMeshComponent* MeshComp,
//    const TArray<FHitResult>& Hits)
//{
//    if (!IsValid(MeshComp)) return;
//
//    AActor* OwnerActor = MeshComp->GetOwner();
//    if (!IsValid(OwnerActor)) return;
//
//    const IGenericTeamAgentInterface* OwnerTeam = Cast<IGenericTeamAgentInterface>(OwnerActor);
//
//    // A 방식: GameplayEventData 생성
//    FGameplayEventData EventData;
//
//    for (const FHitResult& Hit : Hits)
//    {
//        AActor* HitActor = Hit.GetActor();
//        if (!IsValid(HitActor)) continue;
//
//        if (HitActor == OwnerActor)
//            continue;
//
//        UE_LOG(LogTemp, Warning, TEXT("[MeleeTrace] Hit Actor: %s"), *HitActor->GetName());
//        if (GEngine)
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
//                FString::Printf(TEXT("Hit: %s"), *HitActor->GetName()));
//        }
//
//        // A 방식: 중복 타격 방지
//        if (HitActors.Contains(HitActor)) continue;
//
//        // A 방식: 팀 체크
//        if (OwnerTeam)
//        {
//            if (OwnerTeam->GetTeamAttitudeTowards(*HitActor) != TargetTeam)
//                continue;
//        }
//
//        HitActors.Add(HitActor);
//
//        // A 방식: TargetData 추가
//        EventData.TargetData.Add(
//            new FGameplayAbilityTargetData_SingleTargetHit(Hit)
//        );
//
//        // A 방식: Cue 실행
//        TriggerGameplayCue(Hit);
//    }
//
//    // 실제로 타격 대상이 없다면 이벤트 송출 X
//    if (EventData.TargetData.Num() == 0) return;
//
//    // A 방식: GameplayEvent 송출
//    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
//        OwnerActor,
//        EventTag,
//        EventData
//    );
//}

//void UANS_MeleeAttack::TriggerGameplayCue(const FHitResult& Hit) const
//{
//    FGameplayCueParameters CueParam;
//    CueParam.Location = Hit.ImpactPoint;
//    CueParam.Normal = Hit.ImpactNormal;
//
//    for (const FGameplayTag& Tag : CueTags)
//    {
//        UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
//            Hit.GetActor(),
//            Tag,
//            EGameplayCueEvent::Executed,
//            CueParam
//        );
//    }
//}

