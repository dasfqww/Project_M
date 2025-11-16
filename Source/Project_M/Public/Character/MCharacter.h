// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MCharacter.generated.h"

class UMAbilitySystemComponent;
class UMAttributeSet;
class UWidgetComponent;

UCLASS()
class PROJECT_M_API AMCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

	void ServerSideInit();
	void ClientSideInit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<UMAbilitySystemComponent> MAbilitySystemComp;

	UPROPERTY()
	TObjectPtr<UMAttributeSet> MAttributeSet;

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
};
