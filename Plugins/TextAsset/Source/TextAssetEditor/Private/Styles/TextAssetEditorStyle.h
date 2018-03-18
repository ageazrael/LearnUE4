#pragma once

#include "IPluginManager.h"
#include "Brushes/SlateImageBrush.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

/**
* Implements the visual style of the text asset editor UI.
*/
class FTextAssetEditorStyle
	: public FSlateStyleSet
{
public:

	/** Default constructor. */
	FTextAssetEditorStyle()
		: FSlateStyleSet("TextAssetEditorStyle")
	{
		const FVector2D Icon16x16(16.0f, 16.0f);
		const FVector2D Icon20x20(20.0f, 20.0f);
		const FVector2D Icon40x40(40.0f, 40.0f);

		const FString BaseDir = IPluginManager::Get().FindPlugin("TextAsset")->GetBaseDir();
		SetContentRoot(BaseDir / TEXT("Content"));

		// set new styles here, for example...
		//Set("TextAssetEditor.FancyButton", new IMAGE_BRUSH("icon_forward_40x", Icon40x40));

		FSlateStyleRegistry::RegisterSlateStyle(*this);
	}

	/** Destructor. */
	~FTextAssetEditorStyle()
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*this);
	}
};