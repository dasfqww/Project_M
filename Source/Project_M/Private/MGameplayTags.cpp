// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameplayTags.h"

namespace MGameplayTags
{
#pragma region Input
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Ability_BasicAttack, "InputTag.Ability.BasicAttack")
#pragma endregion

#pragma region Ability
	UE_DEFINE_GAMEPLAY_TAG(Ability_None, "Ability.None")
	UE_DEFINE_GAMEPLAY_TAG(Ability_BasicAttack, "Ability.BasicAttack")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Combo_Change, "Ability.Combo.Change")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Combo_Change_Combo01, "Ability.Combo.Change.Combo1")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Combo_Change_Combo02, "Ability.Combo.Change.Combo2")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Combo_Change_Combo03, "Ability.Combo.Change.Combo3")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Combo_Change_Combo04, "Ability.Combo.Change.Combo4")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Combo_Change_End, "Ability.Combo.Change.End")

	UE_DEFINE_GAMEPLAY_TAG(Ability_Combo_Damage, "Ability.Combo.Damage")

#pragma endregion

}
	