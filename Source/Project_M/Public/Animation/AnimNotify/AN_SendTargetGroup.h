// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AN_SendTargetGroup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UAN_SendTargetGroup : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, 
		UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	/*UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	TArray<FName> TargetSocketNames;*/

	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FName SocketName;

	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTag EventTag;

	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	float SocketExtensionOffset = 45.f;
};
