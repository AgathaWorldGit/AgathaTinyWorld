// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "../../../../Plugins/Wwise/Source/AkAudio/Classes/AkGameplayStatics.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAkAudioEvent> RabbitDeathEventObj(*RABBITDEATH_EVENT_PATH);
    
	if (RabbitDeathEventObj.Succeeded())
	{
		RabbitDeathEvent = RabbitDeathEventObj.Object;
		UE_LOG(LogTemp, Warning, TEXT("RabbitDeathEvent loaded successfully."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load RabbitDeathEvent!"));
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* AEnemy::GetBehaviorTree() const
{
	return Tree;
}

APatrolPath* AEnemy::GetPatrolPath() const
{
	return PatrolPath;
}

UAnimMontage*AEnemy::GetMontage() const
{
	return nullptr;
}

int AEnemy::MeleeAttack_Implementation()
{
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}
	return 0;
}

#pragma region Martin
float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
	AActor* DamageCauser)
{

	UE_LOG(LogTemp, Warning, TEXT("TakeDamage called on: %s"), *GetName());
	Health -= DamageAmount;

	if (Health <= 0)
	{
			HandleDeath();
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemy::HandleDeath()
{
	if (RabbitDeathEvent)
	{
		UAkGameplayStatics::PostEvent(
				RabbitDeathEvent, 
				this, 
				0, 
				FOnAkPostEventCallback(), 
				false
			);

		// Include the event name in the log for clarity
		UE_LOG(LogTemp, Warning, TEXT("Played sound: %s"), *RabbitDeathEvent->GetName());
	}

	FString EnemyName = GetClass()->GetName();
	UE_LOG(LogTemp, Log, TEXT("%s has died!"), *GetName());

	if (EnemyName == "Bossbunny_C") 
	{
		UE_LOG(LogTemp, Warning, TEXT("BossBunny has died, loading GameOver Level!"));

		UGameplayStatics::OpenLevel(GetWorld(), "L_GameFinished");
	}
	
	Destroy();
}
#pragma endregion Martin
