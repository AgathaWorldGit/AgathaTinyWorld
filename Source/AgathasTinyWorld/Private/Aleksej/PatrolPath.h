// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPath();

	FVector GetPatrolPoint(int const index)const;
	int Num()const;
	// Called every framec
	// virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	// virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(MakeEditWidget="true",AllowPrivateAccess="true"))
	TArray<FVector>PatrolPoints;

	

};
