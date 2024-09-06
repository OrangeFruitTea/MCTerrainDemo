// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MCTerrainDemo/Generator/HeightGenerator.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MCTerrainGenerationMode.generated.h"

/**
 * 
 */
UCLASS()
class MCTERRAINDEMO_API AMCTerrainGenerationMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	Chunk* TestChunk = new Chunk(FVector2d(0, 0));
	static void TestUpdateChunk(Chunk* Chunk);
	void TestGenerateChunk(const Chunk* Chunk) const;
	void TestCreateBlock(const FVector3d& Pos) const;
};
