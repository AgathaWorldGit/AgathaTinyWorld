// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArghataWorld_AI2GameMode.h"
#include "ArghataWorld_AI2Character.h"
#include "UObject/ConstructorHelpers.h"

AArghataWorld_AI2GameMode::AArghataWorld_AI2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
