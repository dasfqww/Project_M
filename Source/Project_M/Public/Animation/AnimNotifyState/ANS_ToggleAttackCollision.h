// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_ToggleAttackCollision.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UANS_ToggleAttackCollision : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, 
		UAnimSequenceBase* Animation, float TotalDuration, 
		const FAnimNotifyEventReference& EventReference) override;

	void NotifyEnd(USkeletalMeshComponent* MeshComp, 
		UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
