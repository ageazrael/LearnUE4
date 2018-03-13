// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TextAssetEditor : ModuleRules
{
    public TextAssetEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

   //     PublicIncludePaths.AddRange(
   //         new string[] {
   //             "TextAssetEditor/Public"
			//	// ... add public include paths required here ...
			//}
   //         );


        PrivateIncludePaths.AddRange(
            new string[] {
                "TextAssetEditor/Private",
				// ... add other private include paths required here ...
			}
            );


   //     PublicDependencyModuleNames.AddRange(
   //         new string[]
   //         {
   //             "Core",
			//	// ... add other public dependencies that you statically link with here ...
			//}
   //         );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "ContentBrowser",
                "Core",
                "CoreUObject",
                "TextAsset",
                "UnrealEd",
				// "Engine",
				// "Slate",
				// "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                "AssetTools",
                "MainFrame",
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}
