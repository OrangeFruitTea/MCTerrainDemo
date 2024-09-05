// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

// block的六向偏移，辅助检测周边是否有其他方块遮挡
static double GFaceDir_Offset_Offset = 125.f;
static FVector3d GFaceDir_Offset_Fwd = FVector3d(0.f, GFaceDir_Offset_Offset, 0.f);
static FVector3d GFaceDir_Offset_Bwd = -GFaceDir_Offset_Fwd;
static FVector3d GFaceDir_Offset_R = FVector3d(-GFaceDir_Offset_Offset, 0.f, 0.f);
static FVector3d GFaceDir_Offset_L = -GFaceDir_Offset_R;
static FVector3d GFaceDir_Offset_Up = FVector3d(0.f ,0.f, GFaceDir_Offset_Offset);
static FVector3d GFaceDir_Offset_Dwn = -GFaceDir_Offset_Dwn;
static FVector3d GFaceDir_Offset_Dir[6] = {GFaceDir_Offset_Fwd, GFaceDir_Offset_Bwd, GFaceDir_Offset_R, GFaceDir_Offset_L, GFaceDir_Offset_Up,GFaceDir_Offset_Dwn};

// static FString FilePath_M_B_Translucent = TEXT("/Game/MCTerrainDemo/Content/Materials/Blocks/M_B_Translucent");
// static UMaterialInterface* M_Translucent = LoadObject<UMaterialInterface>(nullptr, *FilePath_M_B_Translucent);

UCLASS()
class MCTERRAINDEMO_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void UpdateVisibility();

};
