// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "MInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_M_API UMInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc, typename... VarTypes>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func, VarTypes... Vars);
};

template<class UserObject, typename CallbackFunc>
inline void UMInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, 
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject,
	CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc, typename ...VarTypes>
inline void UMInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject,
	CallbackFunc Func, VarTypes ...Vars)
{
	checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func, Vars...);
	}
}
