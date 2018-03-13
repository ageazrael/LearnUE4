// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TextAsset.h"

#include "ModuleManager.h"
#include "Templates/SharedPointer.h"
#include "AssetTools/TextAssetActions.h"

#define LOCTEXT_NAMESPACE "FTextAssetEditorModule"
class FTextAssetEditorModule
	: public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		auto TextAssetActions = MakeShareable(new FTextAssetActions());
		AssetTools.RegisterAssetTypeActions(TextAssetActions);
		RegisteredAssetTypeActions.Add(TextAssetActions);
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
	}

protected:
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
	TSharedPtr<ISlateStyle> Style;
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTextAssetEditorModule, TextAsset)