// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateColor.h"
#include "TextAssetEditorSettings.generated.h"

/**
 * config=Editor��ʾ�������Ա������ļ�Editor.init�޸�
 */
UCLASS(config=Editor)
class TEXTASSETEDITORUOBJECT_API UTextAssetEditorSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(config, EditAnywhere, Category = Appearance)
	FSlateColor		BackgroundColor;
	
	UPROPERTY(config, EditAnywhere, Category = Appearance)
	FSlateColor		ForegroundColor;

	UPROPERTY(config, EditAnywhere, Category = Appearance)
	FSlateFontInfo	Font;

	UPROPERTY(config, EditAnywhere, Category = Appearance)
	float			Margin;

public:
	UTextAssetEditorSettings();
};
