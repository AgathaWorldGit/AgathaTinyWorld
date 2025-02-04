// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar_Widged.h"

void UHealthBar_Widged::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHealthBar_Widged::SetBarValuePercent(float const value)
{
	HealthBar->SetPercent(value);
}
