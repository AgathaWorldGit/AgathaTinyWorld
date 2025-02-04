// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
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
private:
	bool MontageHasFinished(AEnemy*const npc);
	
};
