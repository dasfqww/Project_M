// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace MGameplayTags
{

#pragma region Input
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Ability_BasicAttack)

#pragma endregion

#pragma region Ability
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_None)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_BasicAttack)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combo_Change)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combo_Change_Combo01)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combo_Change_Combo02)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combo_Change_Combo03)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combo_Change_Combo04)
	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combo_Change_End)

	PROJECT_M_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combo_Damage)

#pragma endregion


}