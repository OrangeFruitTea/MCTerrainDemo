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

void AChunkActor::CreateFace(EBlockType Index, EDirection Direction, FVector Position)
{
	if (!ChunkInfo->Sections.Contains(Index))
    {
    	ChunkInfo->Sections.Emplace(Index, FChunkMeshData());
    }
	const auto Color = FColor::MakeRandomColor();
	const auto Normal = GetNormal(Direction);
	ChunkInfo->Sections[Index].Vertices.Append(GetFaceVertices(Direction, Position));
	ChunkInfo->Sections[Index].Triangles.Append({ChunkInfo->Sections[Index].VertexCount+3, ChunkInfo->Sections[Index].VertexCount+2, ChunkInfo->Sections[Index].VertexCount, ChunkInfo->Sections[Index].VertexCount+2,ChunkInfo->Sections[Index].VertexCount+1, ChunkInfo->Sections[Index].VertexCount});
	ChunkInfo->Sections[Index].Normals.Append({Normal, Normal, Normal, Normal});
	ChunkInfo->Sections[Index].Colors.Append({Color,Color,Color,Color});
	ChunkInfo->Sections[Index].UV0.Append({FVector2d(1/4.f,1/4.f),FVector2d(1/4.f,0),FVector2d(0,0),FVector2d(0,1/4.f)});
	ChunkInfo->Sections[Index].VertexCount += 4;
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
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Calculating...")));
	ApplyMesh();
}

FIntPoint AChunkActor::GetChunkActorIndex()
{
	return ChunkInfo->ChunkIndex;
}

void AChunkActor::CreateQuad(FMask Mask, FIntVector AxisMask, int Width, int Height, FIntVector V1, FIntVector V2,
                             FIntVector V3, FIntVector V4)
{
	const EBlockType Index = Mask.Block;
	const auto Normal = FVector(AxisMask * Mask.Normal);
	const auto TextureIndex = GetTextureIndex(Mask.Block, Normal);
	auto Color = FColor(0, 0, 0, TextureIndex);

	if (!ChunkInfo->Sections.Contains(Index))
	{
		ChunkInfo->Sections.Emplace(Index, FChunkMeshData());
	}

	ChunkInfo->Sections[Index].Vertices.Append({
		FVector(V1)*100 + ChunkInfo->ChunkWorldPosition*99,
		FVector(V2)*100 + ChunkInfo->ChunkWorldPosition*99,
		FVector(V3)*100 + ChunkInfo->ChunkWorldPosition*99,
		FVector(V4)*100 + ChunkInfo->ChunkWorldPosition*99
	});
	ChunkInfo->Sections[Index].Triangles.Append({
		ChunkInfo->Sections[Index].VertexCount,
		ChunkInfo->Sections[Index].VertexCount + 2 + Mask.Normal,
		ChunkInfo->Sections[Index].VertexCount + 2 - Mask.Normal,
		ChunkInfo->Sections[Index].VertexCount + 3,
		ChunkInfo->Sections[Index].VertexCount + 1 - Mask.Normal,
		ChunkInfo->Sections[Index].VertexCount + 1 + Mask.Normal
	});
	ChunkInfo->Sections[Index].Normals.Append({
		Normal,
		Normal,
		Normal,
		Normal
	});
	ChunkInfo->Sections[Index].Colors.Append({
		Color,
		Color,
		Color,
		Color
	});
	auto PreHandle = [](double input) -> double { return input; };
	if (Normal.X == 1 || Normal.X == -1)
	{
		ChunkInfo->Sections[Index].UV0.Append({
			FVector2D(PreHandle(Width), PreHandle(Height)),
			FVector2D(PreHandle(0), PreHandle(Height)),
			FVector2D(PreHandle(Width), PreHandle(0)),
			FVector2D(PreHandle(0), PreHandle(0)),
		});
	}
	else
	{
		ChunkInfo->Sections[Index].UV0.Append({
			FVector2D(PreHandle(Height), PreHandle(Width)),
			FVector2D(PreHandle(Height), PreHandle(0)),
			FVector2D(PreHandle(0), PreHandle(Width)),
			FVector2D(PreHandle(0), PreHandle(0)),
		});
	}

	ChunkInfo->Sections[Index].VertexCount += 4;
}

bool AChunkActor::CompareMask(FMask F1, FMask F2)
{
	return F1.Block == F2.Block && F1.Normal == F2.Normal;
}

void AChunkActor::ApplyMesh()
{
	// ProceduralMesh->ClearAllMeshSections();
	// ProceduralMesh->CreateMeshSection(
	// 	0,
	// 	ChunkInfo->Sections[0].Vertices,
	// 	ChunkInfo->Sections[0].Triangles,
	// 	ChunkInfo->Sections[0].Normals,
	// 	ChunkInfo->Sections[0].UV0,
	// 	ChunkInfo->Sections[0].Colors,
	// 	TArray<FProcMeshTangent>(),
	// 	false);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Section Count: %d"), ChunkInfo->Sections.Num()));
	for (auto& Section : ChunkInfo->Sections)
	{
		FChunkMeshData& MeshData = Section.Value;
		ProceduralMesh->ClearMeshSection(Section.Key);
		ProceduralMesh->CreateMeshSection(
		Section.Key,
		MeshData.Vertices,
		MeshData.Triangles,
		MeshData.Normals,
		MeshData.UV0,
		MeshData.Colors,
		TArray<FProcMeshTangent>(),
		true);
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(M_BlockBase, this);
		ProceduralMesh->SetMaterial(Section.Key, DynamicMaterial);
	}
}

bool AChunkActor::Check(FVector Pos)
{
	if (Pos.X >= MaxBlockWidth || Pos.Y >= MaxBlockWidth || Pos.X < 0 || Pos.Y < 0 || Pos.Z < 0) return true;
	if (Pos.Z >= MaxBlockHeight) return true;
	return ChunkInfo->GetBlock(Pos.X, Pos.Y, Pos.Z) == EBlockType::Air;
}

int32 AChunkActor::GetTextureIndex(EBlockType Type, const FVector& Normal) const
{
	switch (Type)
	{
	case EBlockType::Default: return 0;
	case EBlockType::Stone: return 1;
	case EBlockType::Dirt: return 2;
	case EBlockType::GrassBlock:
		{
			if (Normal == FVector::DownVector) return 2;
			if (Normal == FVector::UpVector) return 4;
			return 3;
		}
	case EBlockType::Sand: return 5;
	case EBlockType::CobbleStone: return 6;
	case EBlockType::Log:
		{
			if (Normal == FVector::UpVector|| Normal == FVector::DownVector) return 8;
			return 7;
		}
	case EBlockType::NetherRock: return 9;
	default: ;
	}
	return 255;
}

void AChunkActor::RenderMesh()
{
	for (int x = 0; x < MaxBlockWidth; x++)
	for (int y = 0; y < MaxBlockWidth; y++)
	for (int z = 0; z < MaxBlockHeight; z++)
	{
		if (ChunkInfo->GetBlock(x,y,z) != EBlockType::Air)
		{
			auto Pos = ChunkInfo->GetBlockWorldPosition(x,y,z);
			// auto Pos = FVector(x,y,z);
			for (const auto Direction : {EDirection::Fwd,EDirection::Right,EDirection::Bwd,EDirection::Left,EDirection::Up,EDirection::Down})
			{
				if (Check(GetPositionInDirection(Direction, Pos)))
				CreateFace(ChunkInfo->GetBlock(x,y,z), Direction, Pos);
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

