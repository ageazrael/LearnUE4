// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UObject.h"
#include "UObject/ObjectMacros.h"

#include "TextAsset.generated.h"


UCLASS(BlueprintType, hidecategories=(Object))
class TEXTASSET_API UTextAsset
	: public UObject
{
	GENERATED_BODY()
public:


	UPROPERTY(BlueprintType, EditAnywhere, Category = "TextAsset")
	FText Text;
};