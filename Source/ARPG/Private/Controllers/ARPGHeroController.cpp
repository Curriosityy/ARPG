// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ARPGHeroController.h"

void AARPGHeroController::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	CurrentTeamID = TeamID;
}

FGenericTeamId AARPGHeroController::GetGenericTeamId() const
{
	return CurrentTeamID;
}
