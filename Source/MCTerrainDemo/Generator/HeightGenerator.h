// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/Chunk.h"

/**
 * 
 */
class MCTERRAINDEMO_API HeightGenerator
{
public:
	static void GenerateDensity(Chunk* Chunk);
	HeightGenerator()=delete;
	~HeightGenerator()=delete;
};
