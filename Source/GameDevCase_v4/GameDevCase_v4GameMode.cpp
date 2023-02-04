// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameDevCase_v4GameMode.h"
#include "GameDevCase_v4HUD.h"
#include "GameDevCase_v4Character.h"
#include "UObject/ConstructorHelpers.h"

AGameDevCase_v4GameMode::AGameDevCase_v4GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGameDevCase_v4HUD::StaticClass();
}
