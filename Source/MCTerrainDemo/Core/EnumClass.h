// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.generated.h"

UENUM()
enum class EDirection { Fwd, Right, Bwd, Left, Up, Down };

UENUM()
enum class ECalculateLevel
{
	Deleted = 0,
	Active
};

UENUM()
enum EBlockType
{
	Null = 0,
	Default,
	Air,
	Dirt,
	Stone,
	GrassBlock,
	Sand,
	CobbleStone,
	Log,
	NetherRock,
	
};
