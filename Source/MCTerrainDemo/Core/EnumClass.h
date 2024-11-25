// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.generated.h"

constexpr int DefaultTestValue = 16;

UENUM()
enum class EDirection : uint8 { Fwd, Right, Bwd, Left, Up, Down };

UENUM()
enum class ECalculateLevel : uint8
{
	Deleted = 0,
	Active
};

UENUM()
enum class EBiomeMainWorld : uint8
{
	None,
	Plains,
	Desert,
	Hills,
	Mountains,
	Ocean,
	SpecialTerrain,
};

UENUM()
enum class EBiomeNether : uint8
{
	Wastelands,
	BasaltDeltas,
	SoulSandValleys,
};

UENUM()
enum class EBiomeEnder : uint8
{
	Highlands,
	Midlands,
	Islands,
	Barrens,
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
