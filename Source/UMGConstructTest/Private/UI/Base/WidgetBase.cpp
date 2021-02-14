// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Base/WidgetBase.h"

#include "Kismet/GameplayStatics.h"

void UWidgetBase::OpenUI_Implementation()
{
	AddToViewport();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = true;
	Controller->SetInputMode(FInputModeGameAndUI());
}

void UWidgetBase::CloseUI_Implementation() 
{
	RemoveFromViewport();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = false;
	Controller->SetInputMode(FInputModeGameOnly());
}