// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"
#include "CombatinterFace.h"
#include "Enemy_AIController.h"
#include "ISourceControlProvider.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RunTime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName=TEXT("Melee Attack");
	
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp,uint8*NodeMemory)
{
	//if player out of range, enemy does not attack
	auto const OutOfRange =!OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		//finish the Task
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
			
	}

	// while in range get the Enemy Con and the enemy itself
	auto const *const cont =OwnerComp.GetAIOwner();
	auto *const npc=Cast<AEnemy>(cont->GetPawn());
	//if the NPC supports the ICombatinterface, cast and call the Execute_MeleeAttck funktion

	if (auto*const icombat=Cast<ICombatinterFace>(npc))
	{
		//necesary check to see if the montage has finished so we dont try and play it again
		if (MontageHasFinished(npc))
		{
			icombat->Execute_MeleeAttack(npc);
		}
	}

	//finish the Task
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_MeleeAttack::MontageHasFinished(AEnemy* const npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}

