// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ButtonWidget.h"

void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//if (ButtonObject)
	//{
	//	ButtonObject->OnClicked.AddDynamic(this, &UButtonWidget::OnButtonClick);
	//}


	//if (ButtonSoundObject)
	//{
	//	//static ConstructorHelpers::FObjectFinder<USoundBase> TempSoundBase(TEXT("SoundWave'/Game/Sounds/Sound_UIBasicClick.Sound_UIBasicClick'"));
	//	//ButtonSoundObject->SoundClassObject = TempSoundBase.Object;
	//}
}
//
//void UButtonWidget::OnButtonClick()
//{
//	//Add Button Sounds
//	PlaySound(ButtonSoundObject);
//
//	OnButtonClick_BlueprintCaller();
//}
