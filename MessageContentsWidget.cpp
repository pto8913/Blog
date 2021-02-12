// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "UI/MessageContentsWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

#include "TimerManager.h"

void UMessageContentsWidget::OpenUI()
{
	if (Contents.IsEmpty()) return;

	SetupStringChar(Contents);
}

void UMessageContentsWidget::CloseUI()
{
	StopTyping();
}

void UMessageContentsWidget::StopTyping()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	for (UWidget* Elem : ContentVB)
	{
		UHorizontalBox* HB = Cast<UHorizontalBox>(Elem);
		HB->ClearChildren();
	}
	ContentVB->ClearChildren();
	Contents.Empty();
	TextBlocks.Empty();
	CurrentHB = nullptr;
}

void UMessageContentsWidget::BeginTyping()
{
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, this, &UMessageContentsWidget::BeginTyping, TypingSpeed, false
	);

	if (TextBlocks.IsValidIndex(TypingPoint) == true)
	{
		UTextBlock* Target = TextBlocks[TypingPoint];
		if (IsValid(Target) == true)
		{
			/* Talking */
			Target->SetRenderOpacity(1.f);
			++TypingPoint;
		}
		else
		{
			/* Finished Talk */
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
	else
	{
		/* Finished Talk */
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void UMessageContentsWidget::GenerateTextBlock(const FString& In)
{
	for (int32 Idx = 0; Idx < In.Len(); ++Idx)
	{
		UTextBlock* NewTextBlock = NewObject<UTextBlock>();
		if (Font.HasValidFont())
		{
			NewTextBlock->SetFont(Font);
		}
		NewTextBlock->SetText(
			FText::FromString(
				In.Mid(Idx, 1)
			)
		);

		NewTextBlock->SetRenderOpacity(0.f);
		TextBlocks.Add(NewTextBlock);
		CurrentHB->AddChildToHorizontalBox(NewTextBlock);
	}
}

TArray<FString> UMessageContentsWidget::SplitLines(FString& In)
{
	TArray<FString> Res;
	In.ParseIntoArray(Res, TEXT("-"));
	return Res;
}

void UMessageContentsWidget::SetupStringChar(FString& In)
{
	int Idx = 0;
	for (const FString& Elem : SplitLines(In))
	{
		CurrentHB = NewObject<UHorizontalBox>();
		ContentVB->AddChild(CurrentHB);
		GenerateTextBlock(Elem);
		++Idx;
	}
	BeginTyping();
}

