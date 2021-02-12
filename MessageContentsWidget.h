// Copyright（C）write by pto8913. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageContentsBase.generated.h"

class UHorizontalBox;
class UVerticalBox;
class UTextBlock;

UCLASS()
class MYPROJECT_API UMessageContentsWidget : public UserWidget
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
	/* 0.01f ~ 0.1f */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pto")
		float TypingSpeed = 0.1f;

	UPROPERTY(BlueprintReadWrite, Category = "pto", meta = (BindWidget))
		UVerticalBox* ContentVB;
		
	/* Turn each character in the line into a TextBlock and hide it. */
	UFUNCTION(BlueprintCallable, Category = "pto")
		void GenerateTextBlock(const FString& In);
	/* Split Contents line by "-" */
	UFUNCTION(BlueprintCallable, Category = "pto")
		TArray<FString> SplitLines(FString& In);
	UFUNCTION(BlueprintCallable, Category = "pto")
		void SetupStringChar(FString& In);
	/* Display TextBlocks at TypingSpeed intervals. */
	UFUNCTION(BlueprintCallable, Category = "pto")
		void BeginTyping();
	/* Stop typing */
	UFUNCTION(BlueprintCallable, Category = "pto")
		void StopTyping();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "pto")
		FTimerHandle TimerHandle;
	/* Current GenerateTextBlock Target HB */
	UPROPERTY(BlueprintReadOnly, Category = "pto")
		UHorizontalBox* CurrentHB;
	/* Pointers to the generated TextBlocks. */
	UPROPERTY(BlueprintReadOnly, Category = "pto")
		TArray<UTextBlock*> TextBlocks;
	UPROPERTY(BlueprintReadOnly, Category = "pto")
		int TypingPoint = 0;
};
