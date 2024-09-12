// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkActor.h"

const int32 bTriangles[] = {2,1,0,0,3,2};
const FVector2d bUVs[] = {FVector2d(0,0),FVector2d(0,0),FVector2d(0,0),FVector2d(0,0)};
const FVector bNormals0[] = {FVector(0,0,1),FVector(0,0,1),FVector(0,0,1),FVector(0,0,1)};
const FVector bNormals1[] = {FVector(0,0,-1),FVector(0,0,-1),FVector(0,0,-1),FVector(0,0,-1)};
const FVector bNormals2[] = {FVector(0,1,0),FVector(0,1,0),FVector(0,1,0),FVector(0,1,0)};
const FVector bNormals3[] = {FVector(0,-1,0),FVector(0,-1,0),FVector(0,-1,0),FVector(0,-1,0)};
const FVector bNormals4[] = {FVector(1,0,0),FVector(1,0,0),FVector(1,0,0),FVector(1,0,0)};
const FVector bNormals5[] = {FVector(-1,0,0),FVector(-1,0,0),FVector(-1,0,0),FVector(-1,0,0)};
const FVector bMask[] = {FVector(0,0,1),FVector(0,0,-1),FVector(0,1,0),FVector(0,-1,0),FVector(1,0,0),FVector(-1,0,0)};

AChunkActor::AChunkActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	ProceduralMesh->SetCastShadow(false);
	SetRootComponent(ProceduralMesh);
}

void AChunkActor::InitChunkActor(Chunk* Info)
{
	ChunkInfo = Info;
	const FString NewString = "ChunkActor_" + FString::FromInt(Info->Index.Key) + "_" + FString::FromInt(Info->Index.Value);
	const TCHAR* NewName = *NewString;
	this->Rename(NewName);
}

// Called when the game starts or when spawned
void AChunkActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChunkActor::RenderBlocks()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2d> UVs;
	TArray<FProcMeshTangent> Tangents;
	TArray<FColor> VertexColors;
	int32 ElementID = 0;
	

	int TriangleNum = 0;
	
	for (int x = 0; x < MaxBlockWidth; x++)
	for (int y = 0; y < MaxBlockWidth; y++)
	for (int z = 0; z < MaxBlockHeight; z++)
	{
		// if (ChunkInfo->BlockDensity[x][y][z] > 0.72f)
		{
			for (int i = 0; i < 6; i++)
			{
				Triangles.Add(bTriangles[0] + TriangleNum + ElementID);
				Triangles.Add(bTriangles[1] + TriangleNum + ElementID);
				Triangles.Add(bTriangles[2] + TriangleNum + ElementID);
				Triangles.Add(bTriangles[3] + TriangleNum + ElementID);
				Triangles.Add(bTriangles[4] + TriangleNum + ElementID);
				Triangles.Add(bTriangles[5] + TriangleNum + ElementID);
				TriangleNum += 4;	// 将四个顶点加入到下一个三角形中

				switch(i)
				{
				case 0:
					{
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Normals.Append(bNormals0, UE_ARRAY_COUNT(bNormals0));
						break;
					}
				case 1:
					{
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Normals.Append(bNormals1, UE_ARRAY_COUNT(bNormals1));
						break;
					}
				case 2:
					{
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Normals.Append(bNormals2, UE_ARRAY_COUNT(bNormals2));
						break;
					}
				case 3:
					{
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Normals.Append(bNormals3, UE_ARRAY_COUNT(bNormals3));
						break;
					}
				case 4:
					{
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Normals.Append(bNormals2, UE_ARRAY_COUNT(bNormals2));
						break;
					}
				case 5:
					{
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(-BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), -BlockSizeHalf + (z * BlockSize)));
						Vertices.Add(FVector(BlockSizeHalf + (x * BlockSize), -BlockSizeHalf + (y * BlockSize), BlockSizeHalf + (z * BlockSize)));
						Normals.Append(bNormals3, UE_ARRAY_COUNT(bNormals3));
						break;
					}
				default:
					break;
				}
				UVs.Append(bUVs, UE_ARRAY_COUNT(bUVs));
				FColor Color = FColor(255, 255, 255, 1);
				VertexColors.Add(Color);
				VertexColors.Add(Color);
				VertexColors.Add(Color);
				VertexColors.Add(Color);
				ElementID += TriangleNum;
			}
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("TriangleNum: %d"), TriangleNum));
	ProceduralMesh->ClearAllMeshSections();
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);

	
}

TArray<FVector> AChunkActor::GetFaceVertices(EDirection Direction, FVector Position) const
{
	TArray<FVector> Vertices;
	for (int i = 0; i < 4; i++)
	{
		Vertices.Add(BlockVertexData[BlockTriangleData[i + static_cast<int32>(Direction) * 4]] * Position);
	}
	return Vertices;
}

void AChunkActor::CreateFace(EDirection Direction, FVector Position)
{
	const auto Color = FColor::MakeRandomColor();
	const auto Normal = GetNormal(Direction);

	ChunkInfo->MeshData.Vertices.Append(GetFaceVertices(Direction, Position));
	ChunkInfo->MeshData.Triangles.Append({VertexCount+3, VertexCount+2,VertexCount+1,VertexCount});
	ChunkInfo->MeshData.Normals.Append({Normal, Normal, Normal, Normal});
	ChunkInfo->MeshData.Colors.Append({Color,Color,Color,Color});
	ChunkInfo->MeshData.UV0.Append({FVector2d(1,1),FVector2d(1,0),FVector2d(0,0),FVector2d(0,1)});
	VertexCount += 4;
	
}


FVector AChunkActor::GetPositionInDirection(EDirection Direction, FVector Position) const
{
	switch (Direction)
	{
	case EDirection::Fwd: return Position + FVector::ForwardVector;
	case EDirection::Bwd: return Position + FVector::BackwardVector;
	case EDirection::Right: return Position + FVector::RightVector;
	case EDirection::Left: return Position + FVector::LeftVector;
	case EDirection::Up: return Position + FVector::UpVector;
	case EDirection::Down: return Position + FVector::DownVector;
	default: throw std::invalid_argument("Invalid direction");
	}
}

FVector AChunkActor::GetNormal(EDirection Direction) const
{
	switch (Direction)
	{
	case EDirection::Fwd: return FVector::ForwardVector;
	case EDirection::Bwd: return FVector::BackwardVector;
	case EDirection::Right: return FVector::RightVector;
	case EDirection::Left: return FVector::LeftVector;
	case EDirection::Up: return FVector::UpVector;
	case EDirection::Down: return FVector::DownVector;
	default: throw std::invalid_argument("Invalid direction");
	}
}

void AChunkActor::ApplyMesh() const
{
	ProceduralMesh->ClearAllMeshSections();
	ProceduralMesh->CreateMeshSection(
		0,
		ChunkInfo->MeshData.Vertices,
		ChunkInfo->MeshData.Triangles,
		ChunkInfo->MeshData.Normals,
		ChunkInfo->MeshData.UV0,
		ChunkInfo->MeshData.Colors,
		TArray<FProcMeshTangent>(),
		false);
}

void AChunkActor::RenderMesh()
{
	for (int x = 0; x < MaxBlockWidth; x++)
	for (int y = 0; y < MaxBlockWidth; y++)
	for (int z = 0; z < MaxBlockHeight; z++)
	{
		if (ChunkInfo->BlockDensity[x][y][z] > 0.7f)
		{
			auto Pos = FVector3d(
				ChunkInfo->ChunkPosition.X*16+x, 
				ChunkInfo->ChunkPosition.Y*16+y,
				z);
			for (const auto Direction : {EDirection::Fwd,EDirection::Right,EDirection::Bwd,EDirection::Left,EDirection::Up,EDirection::Down})
			{
				CreateFace(Direction, Pos);
			}
		}
	}
	ApplyMesh();
}

// Called every frame
void AChunkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

