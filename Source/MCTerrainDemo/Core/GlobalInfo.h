// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "MCTerrainDemo/Tool/IndexTool.h"

/**
 * 
 */
class MCTERRAINDEMO_API GlobalInfo
{
private:
	TMap<uint32, EBlockType> GlobalBlocks;
public:
	GlobalInfo();
	~GlobalInfo();

	EBlockType GetBlockByXYZ(const int X, const int Y, const int Z) const;
	EBlockType GetBlockByXYZ(const FIntVector& Vec) const;
};
