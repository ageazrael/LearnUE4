#include "TextAssetEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "EditorStyleSet.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"

#include "TextAsset.h"
#include "Widgets/STextAssetEditor.h"

#define LOCTEXT_NAMESPACE "FTextAssetEditorToolkit"

DEFINE_LOG_CATEGORY_STATIC(LogTextAssetEditor, Log, All);


namespace TextAssetEditor
{
	static const FName AppIdentifier("TextAssetEditorApp");
	static const FName TabId("TextEditor");
}

FTextAssetEditorToolkit::FTextAssetEditorToolkit(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
	, TextAsset(nullptr)
{}

FTextAssetEditorToolkit::~FTextAssetEditorToolkit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	GEditor->UnregisterForUndo(this);
}

void FTextAssetEditorToolkit::Initialize(UTextAsset* InTextAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	TextAsset = InTextAsset;

	TextAsset->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_TextAssetEditor")
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.66f)
				->Split(
					FTabManager::NewStack()
					->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.1f)
				)
				->Split(
					FTabManager::NewStack()
					->AddTab(TextAssetEditor::TabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.9f)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(
		InMode, 
		InToolkitHost,
		TextAssetEditor::AppIdentifier,
		Layout,
		true,
		true,
		InTextAsset);

	RegenerateMenusAndToolbars();
}


FString FTextAssetEditorToolkit::GetDocumentationLink() const
{
	return FString();
}

void FTextAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_TextAssetEditor", "Text Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(TextAssetEditor::TabId, FOnSpawnTab::CreateSP(this, &FTextAssetEditorToolkit::HandleTabManagerSpawnTab, TextAssetEditor::TabId))
		.SetDisplayName(LOCTEXT("TextEditorTabName", "Text Editor"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LeveEditor.Tabs.Viewports"));
}

void FTextAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(TextAssetEditor::TabId);
}

FText FTextAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Text Asset Editor");
}

FName FTextAssetEditorToolkit::GetToolkitFName() const
{
	return FName("TextAssetEditor");
}

FLinearColor FTextAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

FString FTextAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "TextAsset ").ToString();
}

void FTextAssetEditorToolkit::AddReferencedObjects(FReferenceCollector& InCollector)
{
	InCollector.AddReferencedObject(TextAsset);
}

void FTextAssetEditorToolkit::PostUndo(bool bSuccess)
{
}

void FTextAssetEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}

TSharedRef<SDockTab> FTextAssetEditorToolkit::HandleTabManagerSpawnTab(const FSpawnTabArgs& InArgs, FName InTabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (InTabIdentifier == TextAssetEditor::TabId)
	{
		TabWidget = SNew(STextAssetEditor, TextAsset, Style);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}

#undef LOCTEXT_NAMESPACE