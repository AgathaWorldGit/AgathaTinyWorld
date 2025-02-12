// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MeleeAttack.h"
#include "CombatinterFace.h"
#include "Enemy_AIController.h"
#include "../../../../Plugins/Wwise/Source/AkAudio/Classes/AkGameplayStatics.h"
#include "RunTime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
    NodeName = TEXT("Melee Attack");

    static ConstructorHelpers::FObjectFinder<UAkAudioEvent> RabbitAttackEventObj(*RABBITATTACK_EVENT_PATH);
    
    if (RabbitAttackEventObj.Succeeded())
    {
        RabbitAttackEvent = RabbitAttackEventObj.Object;
        UE_LOG(LogTemp, Warning, TEXT("RabbitAttackEvent loaded successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load RabbitAttackEvent!"));
    }
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Log the start of the task execution
    UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - Task started"));

    // Check if the player is out of range
    auto const OutOfRange = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (OutOfRange)
    {
        // Log that the player is out of range
        UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - Player is out of range, finishing task"));

        // Finish the task
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    // Log that the player is in range
    UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - Player is in range"));

    // Get the Enemy Controller and the enemy itself
    auto const* const cont = OwnerComp.GetAIOwner();
    auto* const npc = Cast<AEnemy>(cont->GetPawn());

    // Log the enemy's name
    if (npc)
    {
        UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - Attacking enemy: %s"), *npc->GetName());
    }

    // Check if the NPC supports the ICombatInterface
    if (auto* const icombat = Cast<ICombatinterFace>(npc))
    {
        // Log that the NPC supports the ICombatInterface
        UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - NPC supports ICombatInterface"));

        // Check if the montage has finished so we don't try to play it again

#pragma region Martin
        ApplyDamageToPlayer(npc);
#pragma endregion Martin
        
        if (MontageHasFinished(npc))
        {
            // Log that the montage has finished and the attack is being executed
            UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - Montage has finished, executing melee attack"));

            // Execute the melee attack
            icombat->Execute_MeleeAttack(npc);

            // Apply damage to the player
        }
        else
        {
            // Log that the montage is still playing
            UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - Montage is still playing, waiting to finish"));
        }
    }
    else
    {
        // Log that the NPC does not support the ICombatInterface
        UE_LOG(LogTemp, Warning, TEXT("UBTTask_MeleeAttack::ExecuteTask - NPC does not support ICombatInterface"));
    }

    npc->GetWorld()->GetTimerManager().SetTimer(AttackCooldownTimerHandle, [this, &OwnerComp](){
        FinishAttackTask(&OwnerComp);
    }, 2.0f, false);

    // Log the completion of the task
    UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ExecuteTask - Task finished"));

    // Finish the task
    FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
    return EBTNodeResult::InProgress;
}

bool UBTTask_MeleeAttack::MontageHasFinished(AEnemy* const npc)
{
    if (npc && npc->GetMesh() && npc->GetMesh()->GetAnimInstance())
    {
        bool bIsMontageStopped = npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
        // Log the montage state
        UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::MontageHasFinished - Montage stopped: %s"), bIsMontageStopped ? TEXT("True") : TEXT("False"));
        return bIsMontageStopped;
    }

    // Log that the montage check failed due to invalid pointers
    UE_LOG(LogTemp, Warning, TEXT("UBTTask_MeleeAttack::MontageHasFinished - Invalid NPC, Mesh, or AnimInstance"));
    return false;
}

#pragma region Martin
void UBTTask_MeleeAttack::FinishAttackTask(UBehaviorTreeComponent* OwnerComp)
{
    if (OwnerComp)
    {
        UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::FinishAttackTask - Cooldown complete, finishing task"));
        FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
        //EBTNodeResult::Succeeded;
    }
}

void UBTTask_MeleeAttack::ApplyDamageToPlayer(AEnemy* const npc)
{
    // Get the world context
    const UWorld* World = npc->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("UBTTask_MeleeAttack::ApplyDamageToPlayer - World is null"));
        return;
    }

    // Get the first player controller
    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("UBTTask_MeleeAttack::ApplyDamageToPlayer - PlayerController is null"));
        return;
    }

    // Get the player character
    ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("UBTTask_MeleeAttack::ApplyDamageToPlayer - PlayerCharacter is null"));
        return;
    }

    // Ensure the player character is not the same as the enemy
    if (PlayerCharacter == npc)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBTTask_MeleeAttack::ApplyDamageToPlayer - Attempted to attack self!"));
        return;
    }

    // Define the damage event
    const FDamageEvent DamageEvent;

    if (RabbitAttackEvent)
    {
        UAkGameplayStatics::PostEvent(
                RabbitAttackEvent, 
                npc, 
                0, 
                FOnAkPostEventCallback(), 
                false
            );

        // Include the event name in the log for clarity
        UE_LOG(LogTemp, Warning, TEXT("Played sound: %s"), *RabbitAttackEvent->GetName());
    }
    
    // Apply damage to the player
    PlayerCharacter->TakeDamage(Damage, DamageEvent, PlayerController, npc);

    // Log the damage application
    UE_LOG(LogTemp, Log, TEXT("UBTTask_MeleeAttack::ApplyDamageToPlayer - Applied %f damage to player: %s"), Damage, *PlayerCharacter->GetName());
}
#pragma endregion Martin