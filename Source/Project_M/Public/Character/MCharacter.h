// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Type/GameplayAbilityType.h"
#include "MCharacter.generated.h"

class UMAbilitySystemComponent;
class UMAttributeSet;
class UWidgetComponent;
class UBoxComponent;
class UPawnCombatComponent;
class UGameplayAbility;

UCLASS()
class PROJECT_M_API AMCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

	void ServerSideInit();
	void ClientSideInit();

	const TMap<EMAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities()const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
#pragma region Ability
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<UMAbilitySystemComponent> MAbilitySystemComp;

	UPROPERTY()
	TObjectPtr<UMAttributeSet> MAttributeSet;
#pragma endregion

#pragma region Collsion
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UBoxComponent> LeftHandCollisionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName LeftHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UBoxComponent> RightHandCollisionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName RightHandCollisionBoxAttachBoneName;

	UFUNCTION()
	void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UPawnCombatComponent> CombatComponent;

#pragma region UI

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<UWidgetComponent> OverheadWidgetComp;

	void ConfigOverheadStatWidget();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float CheckInterval = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float CheckRangeSquared = 10000000.f;

	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;

	void UpdateHeadGaugeVisibility();

#pragma endregion
public:
	FORCEINLINE bool IsLocallyControlledByPlayer() const { return GetController() && GetController()->IsLocalPlayerController(); }
	FORCEINLINE UPawnCombatComponent* GetCombatSystemComponent() const { return CombatComponent; }
	FORCEINLINE UMAbilitySystemComponent* GetMAbilitySystemComponent() const { return MAbilitySystemComp; }	
};
