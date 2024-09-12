// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.generated.h"

UENUM()
enum EDirection { Fwd, Right, Bwd, Left, Up, Down };

UENUM()
enum EBlockTYpe
{
	Air,
	Stone
};
