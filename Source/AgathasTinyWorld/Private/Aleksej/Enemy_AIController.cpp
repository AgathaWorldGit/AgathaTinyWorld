// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include"Martin/AgathaPaperCharacter.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemy_AIController::AEnemy_AIController(FObjectInitializer const& Objectinitializer) 
{
 SetupPerceptionSystem();
}

void AEnemy_AIController::OnPossess(APawn* InPawn) 
{
	Super::OnPossess(InPawn);
	if(AEnemy*const npc = Cast<AEnemy>(InPawn))
	{
		if (UBehaviorTree* const tree= npc->GetBehaviorTree())
		{
			UBlackboardComponent*b;
			UseBlackboard(tree->BlackboardAsset,b);
			Blackboard=b;
			RunBehaviorTree(tree);
		}	
	}
}


void AEnemy_AIController::SetupPerceptionSystem()
{
	SightConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));
		SightConfig->SightRadius=500.0f;
		SightConfig->LoseSightRadius=SightConfig->SightRadius +25.0f;
		SightConfig->PeripheralVisionAngleDegrees=90.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation =520.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;


		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,&AEnemy_AIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense((*SightConfig));
	}
	
}

void AEnemy_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto*const Ch=Cast<AAgathaPaperCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer",Stimulus.WasSuccessfullySensed());
	}
	
}

