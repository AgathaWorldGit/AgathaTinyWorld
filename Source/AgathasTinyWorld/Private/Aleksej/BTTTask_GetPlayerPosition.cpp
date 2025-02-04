// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTTask_GetPlayerPosition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTTask_GetPlayerPosition::UBTTTask_GetPlayerPosition(FObjectInitializer const& ObjectInitializer):UBTTask_BlackboardBase(ObjectInitializer)
{
	NodeName=TEXT("Get Player Position");
}

EBTNodeResult::Type UBTTTask_GetPlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get player position
	if (auto*const Player=UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{
		//get player location to use as an player
		auto const Playerlocation =Player->GetActorLocation();
		if (SearchRandom)
		{
			FNavLocation Loc;
			//get the navigation system and generates a random location near the player
			if (auto*const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				//try to get a random location near the player
				if (NavSys->GetRandomPointInNavigableRadius(Playerlocation,SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
					FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
				
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),Playerlocation);
			FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
