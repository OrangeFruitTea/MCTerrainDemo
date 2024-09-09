// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainDemo/Core/GlobalInfo.h"

GlobalInfo::GlobalInfo()
{
}

GlobalInfo::~GlobalInfo()
{
}

void GlobalInfo::AddBlock(const FVector& Pos, int32 BlockID)
{
	uint64 Index = NoiseTool::Index(Pos.X, Pos.Y, Pos.Z);
	GlobalBlocks.Emplace(Index, BlockID);
	Blocks2Display.Emplace(Index, BlockID);
}

void GlobalInfo::RemoveBlock(const FVector& Pos)
{
	uint64 Index = NoiseTool::Index(Pos.X, Pos.Y, Pos.Z);
	GlobalBlocks.Emplace(Index, 0);
}

int32* GlobalInfo::FindBlock(const FVector& Pos)
{
	int32* Res = GlobalBlocks.Find(NoiseTool::Index(Pos.X, Pos.Y, Pos.Z));
	return Res;
}

TArray<BlockData>& GlobalInfo::GetBlocks2Display()
{
	return Blocks2Display;
}
