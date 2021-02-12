// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#include "UI/MessageContentsWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

#include "TimerManager.h"

void UMessageContentsBase::OpenUI()
{
	HBs = { ContentHB_Row1, ContentHB_Row2, ContentHB_Row3, ContentHB_Row4 };

	if (Contents.IsEmpty()) return;

	SetupStringChar(Contents);
}

void UMessageContentsBase::StopTyping()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	CloseUI();
}

void UMessageContentsBase::BeginTyping()
{
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, this, &UMessageContentsBase::BeginTyping, TypingSpeed, false
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

void UMessageContentsBase::GenerateTextBlock(const FString& In)
{
	for (int32 Idx = 0; Idx < In.Len(); ++Idx)
	{
		UTextBlock* NewTextBlock = NewObject<UTextBlock>();
		if (Font.HasValidFont())
		{
			Font.Size = FontSize;
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

TArray<FString> UMessageContentsBase::SplitLines(FString& In)
{
	TArray<FString> Res;
	In.ParseIntoArray(Res, TEXT("-"));
	return Res;
}

void UMessageContentsBase::SetupStringChar(FString& In)
{
	int Idx = 0;
	for (const FString& Elem : SplitLines(In))
	{
		CurrentHB = HBs[Idx];
		GenerateTextBlock(Elem);
		++Idx;
	}
	BeginTyping();
}

void UMessageContentsBase::CloseUI()
{
	for (UHorizontalBox*& Elem : HBs)
	{
		Elem->ClearChildren();
	}
	HBs.Empty();
	Contents.Empty();
}
