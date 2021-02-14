// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/WidgetBase.h"
#include "ptoButtonWidgetBase.generated.h"

class UButton;
class UVerticalBox;
class UTextBlock;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FptoOnClickedEvent);
DECLARE_MULTICAST_DELEGATE(FptoOnClickedEventNative);

/**
 * 
 */
UCLASS()
class UMGCONSTRUCTTEST_API UptoButtonWidgetBase : public UWidgetBase
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "pto", meta = (BindWidget))
		UVerticalBox* ptoVB;
	UPROPERTY(BlueprintReadOnly, Category = "pto", meta = (BindWidget))
		UButton* ptoButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pto")
		FName ptoImageName;
	UPROPERTY(BlueprintReadOnly, Category = "pto")
		UImage* ptoImage;
public:	
	UFUNCTION(BlueprintCallable, Category = "pto")
		void PreClickedButton();
	int32 ClickedNum = 0;

	UFUNCTION(BlueprintCallable, Category = "pto")
		void ClickedButton();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FptoOnClickedEvent OnClicked;
	FptoOnClickedEventNative OnClickedNative;

	UPROPERTY(BlueprintReadOnly, Category = "pto")
		UTextBlock* PreCreatedText;

	UPROPERTY(BlueprintReadOnly, Category = "pto")
		UTextBlock* CreatedText;
};
