// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageContentsBase.generated.h"

class UHorizontalBox;
class UVerticalBox;
class UTextBlock;

UCLASS()
class PTOPROJECT_API UMessageContentsBase : public UserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "pto")
		virtual void OpenUI();
  UFUNCTION(BlueprintCallable, Category = "pto")
  	virtual void CloseUI();

	/*
		The new line is a "-"
		For example, I-like-apple is
		I
		like
		apple
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto")
		FString Contents;

	/* Font */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto")
		FSlateFontInfo Font;

	UPROPERTY(BlueprintReadWrite, Category = "pto|UI|Message", meta = (BindWidget))
		UVerticalBox* ContentVB;
	/* Turn each character in the line into a TextBlock and hide it. */
	UFUNCTION(BlueprintCallable, Category = "pto|UI|Message")
		void GenerateTextBlock(const FString& In);
	/* Split Contents line by "-" */
	UFUNCTION(BlueprintCallable, Category = "pto|UI|Message")
		TArray<FString> SplitLines(FString& In);
	UFUNCTION(BlueprintCallable, Category = "pto|UI|Message")
		void SetupStringChar(FString& In);
	/* Display TextBlocks at TypingSpeed intervals. */
	UFUNCTION(BlueprintCallable, Category = "pto|UI|Message")
		void BeginTyping();
	/* Stop typing */
	UFUNCTION(BlueprintCallable, Category = "pto|UI|Message")
		void StopTyping();

	/* 0.01f ~ 0.1f */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto|UI|Message")
		float TypingSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto|UI|Message")
		int32 FontSize = 20;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "pto|UI|Message")
		FTimerHandle TimerHandle;
	/* Current GenerateTextBlock Target HB */
	UPROPERTY(BlueprintReadWrite, Category = "pto|UI|Message")
		UHorizontalBox* CurrentHB;
	/* Pointers to the generated TextBlocks. */
	UPROPERTY(BlueprintReadWrite, Category = "pto|UI|Message")
		TArray<UTextBlock*> TextBlocks;

	UPROPERTY(BlueprintReadWrite, Category = "pto|UI|Message")
		int TypingPoint = 0;
};
