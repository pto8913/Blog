// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UMGCONSTRUCTTEST_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "pto")
		void OpenUI();
	virtual void OpenUI_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "pto")
		void CloseUI();
	virtual void CloseUI_Implementation();
};
