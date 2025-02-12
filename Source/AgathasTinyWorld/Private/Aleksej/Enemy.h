// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "CCpAICharackterBase.h"
#include "PatrolPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatinterFace.h"
#include "../../../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
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

	// Martin ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage = 5.0f;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void HandleDeath();
	// Martin ---
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Martin --
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	UAkAudioEvent* RabbitDeathEvent;
	// Martin --
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	APatrolPath* PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage*Montage;

	// Martin ---
	const FString RABBITDEATH_EVENT_PATH = FString(TEXT("/Script/AkAudio.AkAudioEvent'/Game/WwiseAudio/Events/Default_Work_Unit/RabbitDeath.RabbitDeath'"));
	// Martin ---
};
