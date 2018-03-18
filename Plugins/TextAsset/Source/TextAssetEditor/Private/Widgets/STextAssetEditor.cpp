// Fill out your copyright notice in the Description page of Project Settings.

#include "STextAssetEditor.h"
#include "SlateOptMacros.h"
#include "Styling/SlateColor.h"
#include "Widgets/SBoxPanel.h"

#include "TextAsset.h"

#include "TextAssetEditorSettings.h"

#define LOCTEXT_NAMESPACE "STExtAssetEditor"


STextAssetEditor::~STextAssetEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STextAssetEditor::Construct(const FArguments& InArgs, UTextAsset* InTextAsset, const TSharedRef<ISlateStyle>& InStyle)
{
	TextAsset = InTextAsset;

	auto Settings = GetDefault<UTextAssetEditorSettings>();
	ChildSlot
	[
		// Populate the widget
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SAssignNew(EditableTextBox, SMultiLineEditableTextBox)
					.BackgroundColor((Settings != nullptr) ? Settings->BackgroundColor : FLinearColor::White)
					.ForegroundColor((Settings != nullptr) ? Settings->ForegroundColor : FLinearColor::Black)
					.Font((Settings != nullptr) ? Settings->Font : FSlateFontInfo())
					.Margin((Settings != nullptr) ? Settings->Margin : 4.0f)
					.OnTextChanged(this, &STextAssetEditor::HandleEditableTextBoxTextChanged)
					.OnTextCommitted(this, &STextAssetEditor::HandleEditableTextBoxTextCommitted)
					.Text(TextAsset->Text)
			]
	];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &STextAssetEditor::HandleTextAssetPropertyChanged);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STextAssetEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	TextAsset->MarkPackageDirty();
}

void STextAssetEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	TextAsset->Text = EditableTextBox->GetText();
}

void STextAssetEditor::HandleTextAssetPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == TextAsset)
		EditableTextBox->SetText(TextAsset->Text);
}

#undef LOCTEXT_NAMESPACE