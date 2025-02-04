// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandomPosition.h"
#include "Enemy_AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomPosition::UBTTask_GetRandomPosition(FObjectInitializer const& ObjectInitializer):UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName="Get random position";
}

EBTNodeResult::Type UBTTask_GetRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get AI controller and its npc
	if (auto*const cont =Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		if (auto*const npc =cont->GetPawn())
		{
			//obtain npc location to use an origin
			auto const Origin=npc->GetActorLocation();


			//get the navigation sysetem and genarate a random location
			if (auto*const NavSys=UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation NavLoc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin,SearchRadius,NavLoc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),NavLoc.Location);
				}

				//finish with succes
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			
		}
	}
	return EBTNodeResult::Failed;
}


