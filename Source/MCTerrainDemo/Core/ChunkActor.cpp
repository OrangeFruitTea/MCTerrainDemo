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
	const FString NewString = "ChunkActor_" + FString::FromInt(Info->ChunkIndex.X) + FString::FromInt(Info->ChunkIndex.Y);
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
		Vertices.Add(BlockVertexData[BlockTriangleData[i + static_cast<int32>(Direction) * 4]] + Position);
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

void AChunkActor::RenderMeshGreedy()
{
	const int AxisLimit[3] = {MaxBlockWidth, MaxBlockWidth, MaxBlockHeight};
	// 在XYZ三个轴方向进行扫描
	for (int Axis = 0; Axis < 3; ++Axis)
	{
		const int Axis1 = (Axis + 1) % 3;
		const int Axis2 = (Axis + 2) % 3;
		
		const int MainAxisLimit = AxisLimit[Axis];
		const int Axis1Limit = AxisLimit[Axis1];
		const int Axis2Limit = AxisLimit[Axis2];

		auto DeltaAxis1 = FIntVector::ZeroValue;
		auto DeltaAxis2 = FIntVector::ZeroValue;

		auto ChunkItr = FIntVector::ZeroValue;
		auto AxisMask = FIntVector::ZeroValue;

		AxisMask[Axis] = 1;

		TArray<FMask> Mask;
		Mask.SetNum(Axis1Limit * Axis2Limit);

		// 检查chunk的每一侧切片
		for (ChunkItr[Axis] = -1; ChunkItr[Axis] < MainAxisLimit; )
		{
			int N = 0;
			for (ChunkItr[Axis2] = 0; ChunkItr[Axis2] < Axis2Limit; ++ChunkItr[Axis2])
			{
				for (ChunkItr[Axis1] = 0; ChunkItr[Axis1] < Axis1Limit; ++ChunkItr[Axis1])
				{
					const auto CurrentBlock = ChunkInfo->GetBlock(ChunkItr);
					const auto CompareBlock = ChunkInfo->GetBlock(ChunkItr + AxisMask);

					const bool CurrentBlockOpaque = (CurrentBlock != EBlockType::Air && CurrentBlock != EBlockType::Null);
					const bool CompareBlockOpaque = (CompareBlock != EBlockType::Air && CurrentBlock != EBlockType::Null);
					if (CurrentBlockOpaque == CompareBlockOpaque)
					{
						Mask[N++] = FMask{EBlockType::Null, 0};
					} else if (CurrentBlockOpaque)
					{
						Mask[N++] = FMask{CurrentBlock, 1};
					} else
					{
						Mask[N++] = FMask{CompareBlock, -1};
					}
				}
			}
			++ChunkItr[Axis];
			N = 0;
			// 根据mask生成Mesh
			for (int j = 0; j < Axis2Limit; ++j)
			{
				for (int i = 0; i < Axis1Limit;)
				{
					if (Mask[N].Normal != 0)
					{
						const auto CurrentMask = Mask[N];
						ChunkItr[Axis1] = i;
						ChunkItr[Axis2] = j;
						int Width = 1;
						while (i + Width < Axis1Limit && CompareMask(Mask[N+Width], CurrentMask)) Width++;
						int Height = 1;
						bool Done = false;
						for (; j + Height < Axis2Limit; Height++)
						{
							for (int k = 0; k < Width; k++)
							{
								if (CompareMask(Mask[N + k + Height * Axis1Limit], CurrentMask)) continue;
								Done = true;
								break;
							}
							if (Done) break;
						}
						
						DeltaAxis1[Axis1] = Width;
						DeltaAxis2[Axis2] = Height;
						CreateQuad(
							CurrentMask, AxisMask, Width, Height,
							ChunkItr,
							ChunkItr + DeltaAxis1,
							ChunkItr + DeltaAxis2,
							ChunkItr + DeltaAxis1 + DeltaAxis2);
						DeltaAxis1 = FIntVector::ZeroValue;
						DeltaAxis2 = FIntVector::ZeroValue;

						for (int l = 0; l < Height; ++l)
						{
							for (int k = 0; k < Width; k++)
							{
								Mask[N + k + l * Axis1Limit] = FMask{EBlockType::Null, 0};
							}
						}
						i += Width;
						N += Width;
					}
					else
					{
						i++;
						N++;
					}
				}
			}
		}
	}
	ApplyMesh();
}

void AChunkActor::CreateQuad(FMask Mask, FIntVector AxisMask, int Width, int Height, FIntVector V1, FIntVector V2,
                             FIntVector V3, FIntVector V4)
{
	const auto Normal = FVector(AxisMask * Mask.Normal);
	const auto Color = FColor(0, 0, 0);

	ChunkInfo->MeshData.Vertices.Append({
		FVector(V1)*100 + ChunkInfo->ChunkWorldPosition*99,
		FVector(V2)*100 + ChunkInfo->ChunkWorldPosition*99,
		FVector(V3)*100 + ChunkInfo->ChunkWorldPosition*99,
		FVector(V4)*100 + ChunkInfo->ChunkWorldPosition*99
	});
	ChunkInfo->MeshData.Triangles.Append({
		VertexCount,
		VertexCount + 2 + Mask.Normal,
		VertexCount + 2 - Mask.Normal,
		VertexCount + 3,
		VertexCount + 1 - Mask.Normal,
		VertexCount + 1 + Mask.Normal
	});
	ChunkInfo->MeshData.Normals.Append({
		Normal,
		Normal,
		Normal,
		Normal
	});
	ChunkInfo->MeshData.Colors.Append({
		Color,
		Color,
		Color,
		Color
	});
	if (Normal.X == 1 || Normal.X == -1)
	{
		ChunkInfo->MeshData.UV0.Append({
			FVector2D(Width, Height),
			FVector2D(0, Height),
			FVector2D(Width, 0),
			FVector2D(0, 0),
		});
	}
	else
	{
		ChunkInfo->MeshData.UV0.Append({
			FVector2D(Height, Width),
			FVector2D(Height, 0),
			FVector2D(0, Width),
			FVector2D(0, 0),
		});
	}

	VertexCount += 4;
}

bool AChunkActor::CompareMask(FMask F1, FMask F2)
{
	return F1.Block == F2.Block && F1.Normal == F2.Normal;
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

bool AChunkActor::Check(FVector Pos)
{
	if (Pos.X >= MaxBlockWidth || Pos.Y >= MaxBlockWidth || Pos.X < 0 || Pos.Y < 0 || Pos.Z < 0) return true;
	if (Pos.Z >= MaxBlockHeight) return true;
	return ChunkInfo->GetBlock(Pos.X, Pos.Y, Pos.Z) == EBlockType::Air;
}

void AChunkActor::RenderMesh()
{
	for (int x = 0; x < MaxBlockWidth; x++)
	for (int y = 0; y < MaxBlockWidth; y++)
	for (int z = 0; z < MaxBlockHeight; z++)
	{
		if (ChunkInfo->GetBlock(x,y,z) != EBlockType::Air)
		{
			// auto Pos = FVector3d(
			// 	ChunkInfo->ChunkIndex.X+x, 
			// 	ChunkInfo->ChunkIndex.Y+y,
			// 	z);
			auto Pos = ChunkInfo->GetBlockWorldPosition(x,y,z);
			// auto Pos = FVector(x,y,z);
			for (const auto Direction : {EDirection::Fwd,EDirection::Right,EDirection::Bwd,EDirection::Left,EDirection::Up,EDirection::Down})
			{
				if (Check(GetPositionInDirection(Direction, Pos)))
				CreateFace(Direction, Pos);
			}
			// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Red, FString::Printf(TEXT("Block Position: (%f, %f, %f)"), Pos.X, Pos.Y, Pos.Z));
			// GetWorld()->SpawnActor<ABlock>(Pos * 1.75, FRotator::ZeroRotator);
		}
	}
	ApplyMesh();
}

// Called every frame
void AChunkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

