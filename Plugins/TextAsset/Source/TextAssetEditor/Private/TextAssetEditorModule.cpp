// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TextAsset.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ModuleManager.h"
#include "Templates/SharedPointer.h"
#include "AssetTools/TextAssetActions.h"
#include "Styles/TextAssetEditorStyle.h"


///
/// Module分离出UObject这样可以通过Hotload实现模块的动态加载与卸载
///
#define LOCTEXT_NAMESPACE "FTextAssetEditorModule"
class FTextAssetEditorModule
	: public IModuleInterface
	, public IHasMenuExtensibility
	, public IHasToolBarExtensibility
{
public:

	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override
	{
		return MenuExtensibilityManager;
	}
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override
	{
		return ToolBarExtensibilityManager;
	}

	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		Style = MakeShareable(new FTextAssetEditorStyle());

		auto TextAssetActions = MakeShareable(new FTextAssetActions(Style.ToSharedRef()));
		AssetTools.RegisterAssetTypeActions(TextAssetActions);
		RegisteredAssetTypeActions.Add(TextAssetActions);

		MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
		ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);
	}
	virtual void ShutdownModule() override
	{
		// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
		// we call this function before unloading the module.
		FAssetToolsModule * AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
		if (AssetToolsModule != nullptr)
		{
			IAssetTools& AssetTools = AssetToolsModule->Get();

			for (auto Action : RegisteredAssetTypeActions)
			{
				AssetTools.UnregisterAssetTypeActions(Action);
			}
		}

		RegisteredAssetTypeActions.Empty();

		MenuExtensibilityManager.Reset();
		ToolBarExtensibilityManager.Reset();
	}

protected:
	TArray<TSharedRef<IAssetTypeActions>>	RegisteredAssetTypeActions;
	TSharedPtr<ISlateStyle>					Style;

	TSharedPtr<FExtensibilityManager>		MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager>		ToolBarExtensibilityManager;
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTextAssetEditorModule, TextAsset)