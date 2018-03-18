// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

class FText;
class ISlateStyle;
class UTextAsset;

/**
 * 
 */
class STextAssetEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STextAssetEditor)
	{}
	SLATE_END_ARGS()

public:

	virtual ~STextAssetEditor();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, UTextAsset* InTextAsset, const TSharedRef<ISlateStyle>& InStyle);

private:
	void HandleEditableTextBoxTextChanged(const FText& NewText);

	void HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType);

	void HandleTextAssetPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);


private:
	TSharedPtr<SMultiLineEditableTextBox> EditableTextBox;

	UTextAsset* TextAsset;
};
