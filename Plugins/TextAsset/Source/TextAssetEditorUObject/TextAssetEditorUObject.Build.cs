// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TextAssetEditorUObject : ModuleRules
{
    public TextAssetEditorUObject(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] {
                "TextAssetEditorUObject/Public"
				// ... add public include paths required here ...
			});
        PrivateIncludePaths.AddRange(new string[] {
                "TextAssetEditorUObject/Private",
				// ... add other private include paths required here ...
			});


        PublicDependencyModuleNames.AddRange(new string[] {
                "Core",
				// ... add other public dependencies that you statically link with here ...
			});
        PrivateDependencyModuleNames.AddRange(new string[] {
                "ContentBrowser",
                "Core",
                "CoreUObject",
                "TextAsset",
                "Settings",
                "Slate",
                "SlateCore",
                "UnrealEd",
				// ... add private dependencies that you statically link with here ...	
			});

        DynamicallyLoadedModuleNames.AddRange(new string[] {
				// ... add any modules that your module loads dynamically here ...
			});
    }
}
