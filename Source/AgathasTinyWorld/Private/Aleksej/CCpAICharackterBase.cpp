// Fill out your copyright notice in the Description page of Project Settings.

#include "CCpAICharackterBase.h"
#include "Const.h"
#include "HealthBar_Widged.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACCpAICharackterBase::ACCpAICharackterBase() :
WidgetComponent{CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue"))},Health{MaxHealth}
{
 	// Set this character to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	if (WidgetComponent)
	{
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(defs::HealthBarZ);
		// static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{TEXT("/Game/UI/BP_HealthBar")};
		// if (WidgetClass.Succeeded())
		// WidgetComponent->SetWidgetClass(WidgetClass.Class);
	}

		
}

// Called when the game starts or when spawned
void ACCpAICharackterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCpAICharackterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (auto const widget =Cast<UHealthBar_Widged>(WidgetComponent->GetUserWidgetObject()))
	{
		widget->SetBarValuePercent(Health/ MaxHealth);
	}
}

// Called to bind functionality to input
void ACCpAICharackterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACCpAICharackterBase::GetHealth() const
{
	return Health;
}

float ACCpAICharackterBase::GetMaxHealth() const
{
	return MaxHealth;
}

void ACCpAICharackterBase::SetHealth(float const NewHealth)
{
	Health = NewHealth;
}


