// Fill out your copyright notice in the Description page of Project Settings.


#include "Martin/AgathaGameMode.h"
#include "Martin/AgathaCharacter.h"
#include "Martin/AgathaPlayerController.h"

AAgathaGameMode::AAgathaGameMode()
{
    // Set default pawn class to AgathaCharacter
    DefaultPawnClass = AAgathaCharacter::StaticClass();

    // Set default player controller class to AgathaPlayerController
    PlayerControllerClass = AAgathaPlayerController::StaticClass();
}


