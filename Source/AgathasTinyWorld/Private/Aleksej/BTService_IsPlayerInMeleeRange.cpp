// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMeleeRange.h"
#include "Enemy_AIController.h"
#include "Enemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Melee Range");
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get controller and NPC
	auto const*const cont=Cast<AEnemy_AIController>(OwnerComp.GetAIOwner());
	auto const* const npc =Cast<AEnemy>(cont->GetPawn());

	//get player charackrter
	auto const * const player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	//write true or false to the blackboard key depending on whether or not the player is in range
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),npc->GetDistanceTo(player)<=MeleeRange);
}
