// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkActor.h"

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
	ChunkInfo->MeshData.Triangles.Append({VertexCount+3, VertexCount+2, VertexCount, VertexCount+2,VertexCount+1, VertexCount});
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
				ChunkInfo->Index.Key+x, 
				ChunkInfo->Index.Value+y,
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

