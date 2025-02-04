// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPathindex.h"
#include "Enemy.h"
#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_IncrementPathindex::UBTTask_IncrementPathindex(FObjectInitializer const& ObjectInitializer) :UBTTask_BlackboardBase(ObjectInitializer)
 
{
	NodeName = TEXT("Increment Pathindex");
}

EBTNodeResult::Type UBTTask_IncrementPathindex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//try and get AI Controller
	if (auto*const cont =Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		//try and get the NPC
		if (auto*const NPC  = Cast<AEnemy>(cont->GetPawn()))
		{
			//try and get the blackboard
			if (auto*const BC=OwnerComp.GetBlackboardComponent())
			{
				//get number of patrol points and min and max indices
				auto const NoOfPoints=NPC->GetPatrolPath()->Num();
				auto const MinIndex= 0;
				auto const MaxIndex =NoOfPoints-1;
				auto Index=BC->GetValueAsInt(GetSelectedBlackboardKey());

				//change direction if enmy is at the first or last path point
				if (BDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction=EDirectionType::Reverse;
					}
					else if (Index==MinIndex && Direction==EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}
				
				//write new value of index to blackboard
				BC->SetValueAsInt(GetSelectedBlackboardKey(),(Direction==EDirectionType::Forward?++Index:--Index)%NoOfPoints);

				//finish with success
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
		//something went wrong so fail 
	return EBTNodeResult::Failed;
}
