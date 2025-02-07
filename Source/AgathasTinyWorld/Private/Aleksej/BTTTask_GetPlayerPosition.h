// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTTask_GetPlayerPosition.generated.h"

/**
 * 
 */
UCLASS()
class  UBTTTask_GetPlayerPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTTask_GetPlayerPosition(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Search",meta=(AllowPrivateAccess=true))
	bool SearchRandom =false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Search",meta=(AllowPrivateAccess=true)	)
	float SearchRadius = 1500.0f;
	
};
