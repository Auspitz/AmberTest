// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestGameModeBase.h"

#include "TestPlayerCharacter.h"
#include "TestPlayerController.h"

ATestGameModeBase::ATestGameModeBase()
{
    DefaultPawnClass = ATestPlayerCharacter::StaticClass();
    PlayerControllerClass = ATestPlayerController::StaticClass();
}
