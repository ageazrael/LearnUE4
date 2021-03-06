#include "TextAssetActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "TextAsset.h"
#include "Styling/SlateStyle.h"
#include "Toolkits/TextAssetEditorToolkit.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

FTextAssetActions::FTextAssetActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{
}

bool FTextAssetActions::CanFilter()
{
	return true;
}

void FTextAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

	auto TextAssets = GetTypedWeakObjectPtrs<UTextAsset>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("TextAsset_ReverseText", "Reverse Text"),
		LOCTEXT("TextAsset_ReverseTextToolTip", "Reverse the text stored in the selected text asset(s)."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=] {
				for (auto& TextAsset : TextAssets)
				{
					if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
					{
						TextAsset->Text = FText::FromString(TextAsset->Text.ToString().Reverse());
						TextAsset->PostEditChange();
						TextAsset->MarkPackageDirty();
					}
				}
			}),
			FCanExecuteAction::CreateLambda([=] {
				for (auto& TextAsset : TextAssets)
				{
					if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
						return true;
				}
				return false;
			})
		));
}

uint32 FTextAssetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FText FTextAssetActions::GetName() const
{
	return NSLOCTEXT("TextAssetActions", "AssetType_TextAsset", "Text Asset");
}

UClass* FTextAssetActions::GetSupportedClass() const
{
	return UTextAsset::StaticClass();
}

FColor FTextAssetActions::GetTypeColor() const
{
	return FColor::Blue;
}

bool FTextAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}

void FTextAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> InEditWithinLevelEditor)
{
	EToolkitMode::Type Mode = InEditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto TextAsset = Cast<UTextAsset>(*ObjIt);
		if (TextAsset != nullptr)
		{
			TSharedRef<FTextAssetEditorToolkit> EditorToolkit = MakeShareable(new FTextAssetEditorToolkit(Style));
			EditorToolkit->Initialize(TextAsset, Mode, InEditWithinLevelEditor);
		}
	}
}

class UThumbnailInfo* FTextAssetActions::GetThumbnailInfo(UObject* Asset) const
{
	return nullptr;
}

#undef LOCTEXT_NAMESPACE