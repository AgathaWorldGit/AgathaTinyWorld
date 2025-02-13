// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTAsk_ChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTAsk_ChasePlayer::UBTTAsk_ChasePlayer(FObjectInitializer const& ObjectInitializer):UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName=TEXT("ChasePlayer");
}

EBTNodeResult::Type UBTTAsk_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get target location from blackboard via the enemy controller
	if (auto*const cont=Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		//move to the players location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont,PlayerLocation);

		//finsih with succes
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
		
	}
	return EBTNodeResult::Failed;
}
