// Fill out your copyright notice in the Description page of Project Settings.

#include "Aleksej/BTTask_GetPathPoint.h"
#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include  "Enemy.h"

UBTTask_GetPathPoint::UBTTask_GetPathPoint(FObjectInitializer const& ObjectInitializer):UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName = "Get Path Point";
}

EBTNodeResult::Type UBTTask_GetPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//attempt to get the enemys controller
	if (auto* const cont=Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		//attampt to get the Blackboard component from the behavior tree
		if (auto* const bc=OwnerComp.GetBlackboardComponent())
		{
			//get the current patrol path index from the  blackboard
			auto const index = bc->GetValueAsInt((GetSelectedBlackboardKey()));
			
			if (auto*npc=Cast<AEnemy>(cont->GetPawn()))
			{
				// get the current patrol path vector from the NPC- this is local to the patrol path actor
				auto const Point=npc->GetPatrolPath()->GetPatrolPoint(index);

				//convert the local vector to a global point
				auto const Globalpoint =npc->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				bc->SetValueAsVector(PathPointKeyVector.SelectedKeyName, Globalpoint);
				//finish with succes
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
				
			}
			
		}
	}
	return EBTNodeResult::Failed;
}
