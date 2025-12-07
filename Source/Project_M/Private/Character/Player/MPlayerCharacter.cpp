// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/MPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "GAS/MAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
//#include "EnhancedInputComponent.h"
#include "Component/Input/MInputComponent.h"
#include "GAS/MAbilitySystemComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "MGameplayTags.h"

#include "MDebugHelper.h"

AMPlayerCharacter::AMPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

}

void AMPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (IsValid(OwningPlayerController))
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubSystem
			= OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (IsValid(InputSubSystem))
		{
			InputSubSystem->RemoveMappingContext(InputConfigDataAsset->DefaultMappingContext);
			InputSubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
		}
	}
}

void AMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComp))
	{
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMPlayerCharacter::Jump);
	}*/
	
	UMInputComponent* MInputComponent = CastChecked<UMInputComponent>(PlayerInputComponent);

	MInputComponent->BindNativeInputAction(InputConfigDataAsset, MGameplayTags::InputTag_Jump, 
			ETriggerEvent::Triggered, this, &ThisClass::Jump);
	MInputComponent->BindNativeInputAction(InputConfigDataAsset, MGameplayTags::InputTag_Look,
		ETriggerEvent::Triggered, this, &ThisClass::HandleLookInput);
	MInputComponent->BindNativeInputAction(InputConfigDataAsset, MGameplayTags::InputTag_Move,
		ETriggerEvent::Triggered, this, &ThisClass::HandleMoveInput);
		/*MInputComponent->BindNativeInputAction(InputConfigDataAsset, MGameplayTags::InputTag_Move,
			ETriggerEvent::Triggered, this, &ThisClass::Input_Move);*/
	
	for (const TPair<EMAbilityInputID, UInputAction*>& InputActionPair : GameplayAbilityInputActions)
	{
		MInputComponent->BindAction(InputActionPair.Value, 
			ETriggerEvent::Triggered, this, &ThisClass::HandleAbilityInput, InputActionPair.Key);
	}

	//MInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
	//MInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::HandleAbilityInput);
	
}

void AMPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(InputVal.Y);
	AddControllerYawInput(InputVal.X);

}

void AMPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();

	InputVal.Normalize();

	AddMovementInput(GetMoveFwdDir() * InputVal.Y + GetLookRightDir() * InputVal.X);
}

void AMPlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue, EMAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();

	//int32 InputID = GetMAbilitySystemComponent()->GetInputIDFromTag(InputTag);

	//Debug::Print("bPressd : ", bPressed);

	if (bPressed)
	{
		//GetMAbilitySystemComponent()->AbilityInputPressed(InputTag);
		GetAbilitySystemComponent()->AbilityLocalInputPressed((int32)InputID);
	}

	else
	{
		//GetMAbilitySystemComponent()->AbilityInputReleased(InputTag);
		GetAbilitySystemComponent()->AbilityLocalInputReleased((int32)InputID);

	}
}

//void AMPlayerCharacter::AbilityInputPressed(FGameplayTag InputTag)
//{
//	GetMAbilitySystemComponent()->AbilityInputPressed(InputTag);
//}
//
//void AMPlayerCharacter::AbilityInputReleased(FGameplayTag InputTag)
//{
//	GetMAbilitySystemComponent()->AbilityInputReleased(InputTag);
//}

FVector AMPlayerCharacter::GetLookRightDir() const
{
	return FollowCamera->GetRightVector();
}

FVector AMPlayerCharacter::GetLookFwdDir() const
{
	return FollowCamera->GetForwardVector();
}

FVector AMPlayerCharacter::GetMoveFwdDir() const
{
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}

void AMPlayerCharacter::OnDead()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (IsValid(PlayerController))
	{
		DisableInput(PlayerController);
	}
}

void AMPlayerCharacter::OnRespawn()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (IsValid(PlayerController))
	{
		EnableInput(PlayerController);
	}
}


