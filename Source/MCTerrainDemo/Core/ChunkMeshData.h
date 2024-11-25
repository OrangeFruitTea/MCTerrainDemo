// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChunkMeshData.generated.h"

USTRUCT()
struct FChunkMeshData
{
	GENERATED_BODY();
public:
	int VertexCount = 0;
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2d> UV0;
	// UV1存放对应草地面的温度(x)与湿度(y)
	TArray<FVector2d> UV1;
	void Clear();
};

inline void FChunkMeshData::Clear()
{
	VertexCount = 0;
	Vertices.Empty();
	Triangles.Empty();
	Normals.Empty();
	Colors.Empty();
	UV0.Empty();
	UV1.Empty();
}

