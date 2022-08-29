// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Sound/SoundBase.h"
#include "ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEUE5_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
	/*public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* TextObject;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* ButtonObject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		USoundBase* ButtonSoundObject;

	UFUNCTION()
		void OnButtonClick();

	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonClick_BlueprintCaller();*/
	
};
