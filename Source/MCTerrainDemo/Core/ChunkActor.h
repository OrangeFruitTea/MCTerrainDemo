// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "MCTerrainDemo/Core/Chunk.h"
#include "ChunkActor.generated.h"

inline UMaterialInstanceConstant* M_B_Stone = LoadObject<UMaterialInstanceConstant>(nullptr, TEXT("Engine.MaterialInstanceConstant'/Game/Materials/Blocks/MI_B_Stone.MI_B_Stone'"));

UCLASS()
class MCTERRAINDEMO_API AChunkActor : public AActor
{
	GENERATED_BODY()
private:

	int VertexCount = 0;

	TArray<FVector> VertexData;
	TArray<int32> TriangleData;
	TArray<FVector2d> UVData;

	const FVector BlockVertexData[8] = {
		FVector(BlockSize, BlockSize, BlockSize),
		FVector(BlockSize, 0, BlockSize),
		FVector(BlockSize, 0, 0),
		FVector(BlockSize, BlockSize, 0),
		FVector(0, 0, BlockSize),
		FVector(0, BlockSize, BlockSize),
		FVector(0, BlockSize, 0),
		FVector(0, 0, 0),
	};

	const int BlockTriangleData[24] = {
		0,1,2,3, // forward
		5,0,3,6, // right
		4,5,6,7, // back
		1,4,7,2, // left
		5,4,1,0, // up
		3,2,7,6  // down
	};
	
	Chunk* ChunkInfo;
public:
	UPROPERTY(EditAnywhere, Category="Setup")
	UProceduralMeshComponent* ProceduralMesh;
	
public:
	AChunkActor();
	void InitChunkActor(Chunk* Info);
	// 渲染chunk actor中的方块
	void RenderMesh();
	void RenderMeshGreedy();
private:
	// 渲染区块方块
	TArray<FVector> GetFaceVertices(EDirection Direction, FVector Position) const;
	FVector GetPositionInDirection(EDirection Direction, FVector Position) const;
	FVector GetNormal(EDirection Direction) const;
	void CreateFace(EDirection Direction, FVector Position);

	struct FMask {EBlockType Block; int Normal; };
	// Greedy Render渲染方法
	void CreateQuad(FMask Mask, FIntVector AxisMask, int Width, int Height, FIntVector V1, FIntVector V2, FIntVector V3, FIntVector V4);
	bool CompareMask(FMask F1, FMask F2);
	
	void ApplyMesh();

	bool Check(FVector Pos);

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
