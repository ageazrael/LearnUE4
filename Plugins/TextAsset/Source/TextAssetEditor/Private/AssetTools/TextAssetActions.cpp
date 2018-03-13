#include "TextAssetActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "TextAsset.h"
#include "Styling/SlateStyle.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

FTextAssetActions::FTextAssetActions(/*const TSharedRef<ISlateStyle>& InStyle*/)
//	: Style(InStyle)
{

}

bool FTextAssetActions::CanFilter()
{
	return true;
}

void FTextAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);
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

void FTextAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

class UThumbnailInfo* FTextAssetActions::GetThumbnailInfo(UObject* Asset) const
{
	return nullptr;
}

#undef LOCTEXT_NAMESPACE