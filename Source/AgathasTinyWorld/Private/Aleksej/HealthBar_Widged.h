// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBar_Widged.generated.h"

/**
 * 
 */
UCLASS()
class  UHealthBar_Widged : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetBarValuePercent(float const value);

	
private:
    UPROPERTY(BlueprintReadOnly,meta=(BindWidget,AllowPrivateAccess=true))
	UProgressBar* HealthBar=nullptr;
	
};
