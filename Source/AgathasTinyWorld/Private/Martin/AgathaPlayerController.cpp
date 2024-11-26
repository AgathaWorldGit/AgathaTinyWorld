#include "Martin/AgathaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "Martin/AgathaCharacter.h"

AAgathaPlayerController::AAgathaPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAgathaPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Directly access the pawn using GetPawn(), not GetController()
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            // Ensure your input mapping context is valid and add it
            if (m_pMappingContext)
            {
                Subsystem->AddMappingContext(m_pMappingContext, 0);
            }
        }
    }
}

void AAgathaPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    auto Input = Cast<UEnhancedInputComponent>(InputComponent);

    if (Input && m_pMoveAction)
    {
        // Bind the movement action to the "OnMove" function
        Input->BindAction(m_pMoveAction, ETriggerEvent::Triggered, this, &AAgathaPlayerController::OnMove);
    }
}

void AAgathaPlayerController::OnMove(const FInputActionValue& Value)
{
    // Get the pawn controlled by this player
    AAgathaCharacter* AgathaCharacter = Cast<AAgathaCharacter>(GetPawn());
    if (AgathaCharacter)
    {
        // Extract movement input and pass it to the character
        FVector2D MovementValue = Value.Get<FVector2D>();

        // Log the movement to check if it's working
        UE_LOG(LogTemp, Log, TEXT("Movement Input: X=%f, Y=%f"), MovementValue.X, MovementValue.Y);

        AgathaCharacter->MoveRight(MovementValue.X); // Moving along the X-axis
    }
}

