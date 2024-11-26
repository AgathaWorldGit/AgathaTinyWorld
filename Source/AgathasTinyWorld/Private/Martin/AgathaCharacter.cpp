#include "Martin/AgathaCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputSubsystems.h"

AAgathaCharacter::AAgathaCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAgathaCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AAgathaCharacter::MoveRight(float f_Value)
{
    AddMovementInput(FVector(1.f, 0.f, 0.f), f_Value);
}

void AAgathaCharacter::LightAttack()
{
    UE_LOG(LogTemp, Log, TEXT("Light Attack Executed"));
}

void AAgathaCharacter::HeavyAttack()
{
    UE_LOG(LogTemp, Log, TEXT("Heavy Attack Executed"));
}

void AAgathaCharacter::SpecialAttack()
{
    UE_LOG(LogTemp, Log, TEXT("Special Attack Executed"));
}
