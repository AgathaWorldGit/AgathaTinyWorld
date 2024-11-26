#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "AgathaPlayerController.generated.h"

UCLASS()
class AGATHASTINYWORLD_API AAgathaPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AAgathaPlayerController();

protected:
    virtual void BeginPlay() override;

private:
    const FString MAPPING_CONTEXT_PATH = "/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Agatha.IMC_Agatha'";
    const FString MOVE_ACTION_PATH = "/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_AgathaMove.IA_AgathaMove'";

    UInputMappingContext* m_pMappingContext = nullptr;
    UInputAction* m_pMoveAction = nullptr;

    void OnMove(const FInputActionValue& value);

    virtual void SetupInputComponent() override;
};
