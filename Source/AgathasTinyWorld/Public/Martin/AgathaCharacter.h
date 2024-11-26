// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AgathaCharacter.generated.h"

UCLASS()
class AGATHASTINYWORLD_API AAgathaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Constructor
	AAgathaCharacter();

protected:
	virtual void BeginPlay() override;

public:
    // Input handlers for movement
    void MoveRight(float f_Value);

    // Attack functions
    void LightAttack();
    void HeavyAttack();
    void SpecialAttack();

private:
    // Movement input value
    FVector2D m_v2D_MoveInput;
};
