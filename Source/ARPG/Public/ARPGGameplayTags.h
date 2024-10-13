// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * 
 */
namespace ARPGGameplayTags
{
	/*Input Tags*/
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);

	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);

	/*Player Tags*/
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);

	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Attack_Light_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Attack_Heavy_Axe);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);

	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Finisher);

	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);
	/*Enemy Tags*/
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	/*Shared Tags*/
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact)
	
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage)
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_ComboCount)

	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact)
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death)
	
	ARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death);
}
