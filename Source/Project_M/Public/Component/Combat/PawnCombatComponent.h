// CSM All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	/*UFUNCTION()
	void HandleBodyOverlap(AActor* OtherActor, 
		const FHitResult& SweepResult, UPrimitiveComponent* HitBoxComp);

	void ToggleBodyCollision();*/

	void ToggleBodyCollision(bool bShouldEnable);

};
