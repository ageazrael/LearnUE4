// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AssetTypeActions_Base.h"
#include "Templates/SharedPointer.h"

class ISlateStyle;

class FTextAssetActions
	: public FAssetTypeActions_Base
{
public:
	FTextAssetActions(const TSharedRef<ISlateStyle>& InSlateType);

public:
	virtual bool CanFilter()override;
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;

private:
	TSharedRef<ISlateStyle> Style;
};