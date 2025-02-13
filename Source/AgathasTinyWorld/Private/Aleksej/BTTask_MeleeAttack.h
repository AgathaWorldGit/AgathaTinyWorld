// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class  UBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_MeleeAttack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// Martin --
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	UAkAudioEvent* RabbitAttackEvent;
	// Martin --
private:
    bool MontageHasFinished(AEnemy* const npc);
	
	// MARTIN ----
	void FinishAttackTask(UBehaviorTreeComponent* OwnerComp);
	
	void ApplyDamageToPlayer(AEnemy* npc);
	
	FTimerHandle AttackCooldownTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 300.0f;
	
	const FString RABBITATTACK_EVENT_PATH = FString(TEXT("/Script/AkAudio.AkAudioEvent'/Game/WwiseAudio/Events/Default_Work_Unit/RabbitAttack.RabbitAttack'"));
	// MARTIN ----
};
