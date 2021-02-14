// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Base/ptoButtonWidgetBase.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Engine.h"

bool UptoButtonWidgetBase::Initialize()
{
	bool res = Super::Initialize();

	UWidget* PreptoImage = GetWidgetFromName(ptoImageName);
	if (PreptoImage)
	{
		ptoImage = Cast<UImage>(ptoImage);
	}

	return res;
}

void UptoButtonWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	ClickedNum = 0;

	if (ptoButton)
	{
		ptoButton->OnClicked.AddDynamic(this, &UptoButtonWidgetBase::PreClickedButton);
	}


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("NativePreConstruct"));

}

void UptoButtonWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (ptoButton)
	{
		ptoButton->OnClicked.AddDynamic(this, &UptoButtonWidgetBase::ClickedButton);
	}

	//UWidget* PreptoImage = GetWidgetFromName(ptoImageName);
	//if (PreptoImage)
	//{
	//	ptoImage = Cast<UImage>(ptoImage);
	//}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("NativeConstruct"));
}

void UptoButtonWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();

	ptoButton->OnClicked.Clear();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("NativeDestruct %d"), ClickedNum));

	ClickedNum = 0;
}

void UptoButtonWidgetBase::PreClickedButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PreClicked %d"), ClickedNum));

	if (IsValid(ptoImage))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Pre ptoImage IsValid")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Pre ptoImage IsNotValid")));
	}
	
}

void UptoButtonWidgetBase::ClickedButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Clicked %d"), ClickedNum));
	++ClickedNum;

	if (IsValid(ptoImage))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ptoImage IsValid")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ptoImage IsNotValid")));
	}
}
