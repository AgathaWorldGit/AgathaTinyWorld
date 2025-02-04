// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "CCpAICharackterBase.h"
#include "PatrolPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatinterFace.h"
#include "Animation/AnimMontage.h"
#include "Enemy.generated.h"


UCLASS()
class AEnemy : public ACCpAICharackterBase,public ICombatinterFace
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;

	APatrolPath* GetPatrolPath() const;

	UAnimMontage*GetMontage() const;

	int MeleeAttack_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	APatrolPath* PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage*Montage;

	
};
