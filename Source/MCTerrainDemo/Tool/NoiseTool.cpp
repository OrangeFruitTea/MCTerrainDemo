// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseTool.h"

FVector2d GlobalOffset = {};
FVector GlobalOffset3d = {};


void NoiseTool::RandomPermWithSeed(int32 Seed)
{
	FRandomStream RandomStream(Seed);
	for (int i = 0; i < 256; i++)
	{
		Perm[i] = RandomStream.GetUnsignedInt() % 256;
	}
}

void NoiseTool::RandomPerm()
{
	const int32 Seed = FPlatformTime::Cycles();
	RandomPermWithSeed(Seed);
}

float NoiseTool::Grad(const FVector2d& Position2d, const FVector2d& Vertex)
{
	return FVector2d::DotProduct(Position2d, Vertex);
}

float NoiseTool::GradWithSeed(int Seed, int XPrimed, int YPrimed, float Xd, float Yd)
{
	int Hash = Hash21WithSeed(Seed, XPrimed, YPrimed);
	Hash ^= Hash >> 15;
	Hash &= 127 << 1;
	float Xg = Gradients2D[Hash];
	float Yg = Gradients2D[Hash|1];
	return Xd * Xg + Yd * Yg;
}

float NoiseTool::Grad3d(float X, float Y, float Z, int Hash)
{
	int h = Hash & 15;
	int u = h < 8 ? X : Y;
	int v = h < 4 ? Y : (h == 12 || h == 14 ? X : Z);
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float NoiseTool::Grad3dWithSeed(int Seed, int XPrimed, int YPrimed, int ZPrimed, float Xd, float Yd, float Zd)
{
	int Hash = Hash31WithSeed(Seed, XPrimed, YPrimed, ZPrimed);
	Hash ^= Hash >> 15;
	Hash &= 63 << 2;
	float Xg = Gradients3D[Hash];
	float Yg = Gradients3D[Hash|1];
	float Zg = Gradients3D[Hash|2];
	return Xd * Xg + Yd * Yg + Zd * Zg;
}

float NoiseTool::Grad3d(const FVector3d& Position3d, const FVector3d& Vertex)
{
	return FVector3d::DotProduct(Position3d, Vertex);
}

int32 NoiseTool::Hash11(const int32 Value)
{
	constexpr uint32 Multiplier = 0x9E3779B9;
	uint32 UnValue = static_cast<uint32>(Value);
	const bool IsNegative = Value < 0;
	// 使用位运算混合结果
	uint32 hash = UnValue * Multiplier;
	hash ^= hash >> 16;
	hash *= 0x6C07A965;
	hash ^= hash >> 3;
	// 如果原始值是负数，通过XOR操作添加一个模式来区分哈希值
	if (IsNegative)
		hash ^= 0x80000000; // XOR操作一个模式，确保负数和正数的哈希值不同
	return hash;
}

int32 NoiseTool::Hash21(const FVector2d& Vector)
{
	return (0x9E3779B9* static_cast<int32>(Vector.X) + static_cast<int32>(Vector.Y)) % 1024;
}

int32 NoiseTool::Hash21WithSeed(int Seed, int X, int Y)
{
	int32 Hash = Seed ^ X ^ Y;
	Hash *= 0x27d4eb2d;
	return Hash;
}

int32 NoiseTool::Hash31(const FVector3d& Vector)
{
	return (0x9E3779B9* static_cast<int32>(Vector.X) + 0x6C078965* static_cast<int32>(Vector.Y) + static_cast<int32>(Vector.Z)) % 1024;
}

int32 NoiseTool::Hash31WithSeed(int Seed, int X, int Y, int Z)
{
	int32 Hash = Seed ^ X ^ Y ^ Z;
	Hash *= 0x27d4eb2d;
	return Hash;
}

float NoiseTool::Fade(const float T)
{
	return T*T*T*(T*(T*6-15)+10);
}

void NoiseTool::PreHandlePerlinNoise2d(float X, float Y, const int32 CrystalSize)
{
	// 根据给定点世界坐标与晶格大小确定给定点所在的晶格
	// Pi: 所在晶格的左下顶点的虚拟坐标
	const FVector2d Pi = FVector2d(floor(X/CrystalSize),floor(Y/CrystalSize));
	const FVector2d Vertex[4] = {Pi, FVector2d(Pi.X+1, Pi.Y), FVector2d(Pi.X, Pi.Y+1), FVector2d(Pi.X+1, Pi.Y+1)};
	// 根据晶格顶点坐标赋予随机梯度
	for(int i = 0; i < 4; i++)
	{
		int Index = Hash21(Vertex[i]) % 8;
		CrystalVertex[i] = GGradientVector2d[Index];
	}
	// 更新区块的全局偏移
	GlobalOffset = (FVector2d(X,Y)/ CrystalSize);
}

void NoiseTool::PreHandlePerlinNoise2d(const FVector2d& Position2d, const int32 CrystalSize)
{
	PreHandlePerlinNoise2d(Position2d.X,Position2d.Y, CrystalSize);
}

float NoiseTool::HandlePerlinNoise3d(float X, float Y, float Z, const int32 CrystalSize)
{
	// 获取晶格所属位置
	int32 PiX = floor(X / CrystalSize);
	int32 PiY = floor(Y / CrystalSize);
	int32 PiZ = floor(Z / CrystalSize);
	// 晶格内部偏移
	float x = X - PiX;
	float y = Y - PiY;
	float z = Z - PiZ;
	float u = Fade(x);
	float v = Fade(y);
	float w = Fade(z);
	int A = (Perm[PiX] + Y);
	int B = (Perm[PiX+1] + Y);
	int AA = (Perm[A] + Z);
	int BA = (Perm[B] + Z);
	int AB = (Perm[A+1] + Z);
	int BB = (Perm[B+1] + Z);
	return FMath::Lerp(
					FMath::Lerp(
						FMath::Lerp(Grad3d(x, y, z, Perm[AA]),
									Grad3d(x-1, y, z, Perm[BA]),
									u),
						FMath::Lerp(Grad3d(x, y-1, z, Perm[AB]),
									Grad3d(x-1, y-1, z, Perm[BB]),
									u),
						v),
					FMath::Lerp(
						FMath::Lerp(Grad3d(x, y, z-1, Perm[AA+1]),
									Grad3d(x-1, y, z-1, Perm[BA+1]),
									u),
						FMath::Lerp(Grad3d(x, y-1, z-1, Perm[AB+1]),
									Grad3d(x-1, y-1, z-1, Perm[BB+1]),
									u),
						v),
					w);
	
}

void NoiseTool::PreHandlePerlinNoise3d(float X, float Y, float Z, const int32 CrystalSize)
{
	const FVector Pi = FVector(floor(X / CrystalSize),floor(Y / CrystalSize),floor(Z / CrystalSize));
	const FVector3d Vertex[8] = {Pi, FVector3d(Pi.X+1, Pi.Y, Pi.Z), FVector3d(Pi.X, Pi.Y+1, Pi.Z),FVector3d(Pi.X, Pi.Y, Pi.Z+1),
								FVector3d(Pi.X+1, Pi.Y+1, Pi.Z),FVector3d(Pi.X+1, Pi.Y, Pi.Z+1),FVector3d(Pi.X, Pi.Y+1, Pi.Z+1),FVector3d(Pi.X+1, Pi.Y+1, Pi.Z+1)};
	for(int i = 0; i < 8; i++)
	{
		int Index = Hash31(Vertex[i]) % 12;
		CrystalVertex3d[i] = GGradientVector3d[Index];
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Crystal Vertex: (%f, %f, %f)"), CrystalVertex3d[i].X, CrystalVertex3d[i].Y, CrystalVertex3d[i].Z));
	}
	GlobalOffset3d = (FVector(X,Y,Z)-Pi*CrystalSize)/ CrystalSize;
}

void NoiseTool::PreHandlePerlinNoise3d(const FVector3d& Position3d, const int32 CrystalSize)
{
	PreHandlePerlinNoise3d(Position3d.X,Position3d.Y,Position3d.Z,CrystalSize);
}

float NoiseTool::PerlinNoise2d(const FVector2d& Pos)
{
	// 各晶格顶点梯度与距离作点积
	return FMath::Clamp<float>(
		FMath::Lerp(
			FMath::Lerp(Grad(Pos, CrystalVertex[0]), Grad(Pos, CrystalVertex[1]), Fade(Pos.X)),
			FMath::Lerp(Grad(Pos, CrystalVertex[2]), Grad(Pos, CrystalVertex[3]), Fade(Pos.X)),
			Fade(Pos.Y)),
			-1, 1);
}

float NoiseTool::PerlinNoise3d(float X, float Y, float Z)
{
	return 0;
}

float NoiseTool::PerlinNoise3d(const FVector3d& Position)
{
	FVector3d Pos = Position + GlobalOffset3d;
	return FMath::Clamp<float>(
		FMath::Lerp(
			FMath::Lerp(
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[0]), Grad3d(Pos, CrystalVertex3d[1]), Fade(Pos.X)),
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[2]), Grad3d(Pos, CrystalVertex3d[3]), Fade(Pos.X)),
				Fade(Pos.Y)),
			FMath::Lerp(
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[4]), Grad3d(Pos, CrystalVertex3d[5]), Fade(Pos.X)),
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[6]), Grad3d(Pos, CrystalVertex3d[7]), Fade(Pos.X)),
				Fade(Pos.Y)),
			Fade(Pos.Z)),
			-1, 1);
}

float NoiseTool::SinglePerlin(int Seed, float X, float Y)
{
	int X0 = FMath::Floor(X);
	int Y0 = FMath::Floor(Y);

	float Xd0 = (float)(X - X0);
	float Yd0 = (float)(Y - Y0);
	float Xd1 = Xd0 - 1;
	float Yd1 = Yd0 - 1;

	float Xs = Fade(Xd0);
	float Ys = Fade(Yd0);

	X0 *= PrimeX;
	Y0 *= PrimeY;
	int X1 = X0 + PrimeX;
	int Y1 = Y0 + PrimeY;

	float Xf0 = FMath::Lerp(GradWithSeed(Seed, X0, Y0, Xd0, Yd0), GradWithSeed(Seed, X1, Y0, Xd1, Yd0), Xs);
	float Xf1 = FMath::Lerp(GradWithSeed(Seed, X0, Y1, Xd0, Yd1), GradWithSeed(Seed, X1, Y1, Xd1, Yd1), Xs);

	return FMath::Lerp(Xf0, Xf1, Ys) * 1.4247691104677813f;
}

float NoiseTool::SinglePerlin(int Seed, const FVector2d& Vec)
{
	return SinglePerlin(Seed, Vec.X, Vec.Y);
}

float NoiseTool::SinglePerlin(int Seed, float X, float Y, float Z)
{
	// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Red, FString::Printf(TEXT("x0 y0 z0: (%f, %f, %f)"), X, Y, Z));
	int x0 = FMath::Floor(X);
	int y0 = FMath::Floor(Y);
	int z0 = FMath::Floor(Z);
	

	float xd0 = (float)(X - x0);
	float yd0 = (float)(Y - y0);
	float zd0 = (float)(Z - z0);
	float xd1 = xd0 - 1;
	float yd1 = yd0 - 1;
	float zd1 = zd0 - 1;
	// 缓动函数
	float xs = Fade(xd0);
	float ys = Fade(yd0);
	float zs = Fade(zd0);

	x0 *= PrimeX;
	y0 *= PrimeY;
	z0 *= PrimeZ;
	int x1 = x0 + PrimeX;
	int y1 = y0 + PrimeY;
	int z1 = z0 + PrimeZ;

	float xf00 = FMath::Lerp(Grad3dWithSeed(Seed, x0, y0, z0, xd0, yd0, zd0), Grad3dWithSeed(Seed, x1, y0, z0, xd1, yd0, zd0), xs);
	float xf10 = FMath::Lerp(Grad3dWithSeed(Seed, x0, y1, z0, xd0, yd1, zd0), Grad3dWithSeed(Seed, x1, y1, z0, xd1, yd1, zd0), xs);
	float xf01 = FMath::Lerp(Grad3dWithSeed(Seed, x0, y0, z1, xd0, yd0, zd1), Grad3dWithSeed(Seed, x1, y0, z1, xd1, yd0, zd1), xs);
	float xf11 = FMath::Lerp(Grad3dWithSeed(Seed, x0, y1, z1, xd0, yd1, zd1), Grad3dWithSeed(Seed, x1, y1, z1, xd1, yd1, zd1), xs);

	float yf0 = FMath::Lerp(xf00, xf10, ys);
	float yf1 = FMath::Lerp(xf01, xf11, ys);

	return FMath::Lerp(yf0, yf1, zs) * 0.964921414852142333984375f;
}

float NoiseTool::SinglePerlin(int Seed, const FVector& Vec)
{
	return SinglePerlin(Seed, Vec.X, Vec.Y, Vec.Z);
}

uint64 NoiseTool::Index(const int32 X,const int32 Y, const int32 Z)
{
	constexpr int32 Offset = 16384;
	return (static_cast<uint64>(X+Offset)<<40 | static_cast<uint64>(Y+Offset)<<20 | static_cast<uint64>(Z+Offset));
}

uint64 NoiseTool::Index(const FVector& Vec)
{
	return Index(Vec.X, Vec.Y, Vec.Z);
}

uint64 NoiseTool::Index(const FVector2d& Vec)
{
	return Index(Vec.X, Vec.Y);
}

FVector NoiseTool::UnIndex(uint64 Index)
{
	const int32 Offset = 16384;
	return FVector(
		int32(Index>>40)-Offset,
		int32((Index>>20)&0xFFFFF)-Offset,
		int32(Index&0xFFFFF)-Offset);
	
}
