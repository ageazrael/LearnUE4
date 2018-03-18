// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TextAsset.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ModuleManager.h"
#include "TextAssetEditorSettings.h"

#define LOCTEXT_NAMESPACE "FTextAssetEditorModule"
class FTextAssetEditorUObjectModule
	: public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		// 在编辑器设置中增加TextAsset设置
		auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (SettingsModule != nullptr)
		{
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Editor", "Plugins", "TextAsset",
				LOCTEXT("TextAssetSettingsName", "Text Asset"),
				LOCTEXT("TextAssetSettingsDescription", "Configure the Text Asset plug-in."),
				GetMutableDefault<UTextAssetEditorSettings>()
			);
		}
	}
	virtual void ShutdownModule() override
	{
		auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (SettingsModule != nullptr)
		{
			SettingsModule->UnregisterSettings("Editor", "Plugins", "TextAsset");
		}
	}

protected:
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTextAssetEditorUObjectModule, TextAsset)