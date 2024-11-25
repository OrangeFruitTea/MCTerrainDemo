// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainDemo/Core/GlobalInfo.h"

GlobalInfo::GlobalInfo()
{
}

GlobalInfo::~GlobalInfo()
{
}

EBlockType GlobalInfo::GetBlockByXYZ(const int X, const int Y, const int Z) const
{
	return EBlockType::Null;	
}

EBlockType GlobalInfo::GetBlockByXYZ(const FIntVector& Vec) const
{
	return EBlockType::Null;	
}
