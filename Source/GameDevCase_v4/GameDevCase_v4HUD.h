// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameDevCase_v4HUD.generated.h"

UCLASS()
class AGameDevCase_v4HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameDevCase_v4HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

