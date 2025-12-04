// CSM All Rights Reserved.


#include "Component/Combat/PawnCombatComponent.h"
//#include "Character/Player/MPlayerCharacter.h"
#include "Character/MCharacter.h"
#include "Components/BoxComponent.h"


//void UPawnCombatComponent::HandleBodyOverlap(AActor* OtherActor, 
//	const FHitResult& SweepResult, UPrimitiveComponent* HitBoxComp)
//{
//    // 충돌 박스의 위치
//    FVector BoxLocation = HitBoxComp->GetComponentLocation();
//    FVector BoxForward = HitBoxComp->GetForwardVector();
//
//    // SweepResult의 충돌 위치 (정확한 충돌 지점)
//    FVector ImpactPoint = SweepResult.ImpactPoint;
//}

void UPawnCombatComponent::ToggleBodyCollision(bool bShouldEnable)
{
	AMCharacter* PlayerCharacter = GetOwningPawn<AMCharacter>();

	check(PlayerCharacter);

	//UBoxComponent* LeftHandBoxComponent=PlayerCharacter->
}
