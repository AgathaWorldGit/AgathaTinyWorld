// Copyright Epic Games, Inc. All Rights Reserved.

#include "AgathasTinyWorldGameMode.h"
#include "AgathasTinyWorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAgathasTinyWorldGameMode::AAgathasTinyWorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
