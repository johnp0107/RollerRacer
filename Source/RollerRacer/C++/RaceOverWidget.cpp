// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceOverWidget.h"

void URaceOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FinishPositionImageList.Add(FirstPlaceImage);
	FinishPositionImageList.Add(SecondPlaceImage);
	FinishPositionImageList.Add(ThirdPlaceImage);
	FinishPositionImageList.Add(FourthPlaceImage);
	FinishPositionImageList.Add(FifthPlaceImage);
	FinishPositionImageList.Add(SixthPlaceImage);
	FinishPositionImageList.Add(SeventhPlaceImage);
	FinishPositionImageList.Add(EighthPlaceImage);
	FinishPositionImageList.Add(NinthPlaceImage);
	FinishPositionImageList.Add(TenthPlaceImage);
	FinishPositionImageList.Add(EleventhPlaceImage);
	FinishPositionImageList.Add(TwelfthPlaceImage);
	FinishPositionImageList.Add(ThirteenthPlaceImage);

	FinishPositionNumberList.Add(FirstPlaceText);
	FinishPositionNumberList.Add(SecondPlaceText);
	FinishPositionNumberList.Add(ThirdPlaceText);
	FinishPositionNumberList.Add(FourthPlaceText);
	FinishPositionNumberList.Add(FifthPlaceText);
	FinishPositionNumberList.Add(SixthPlaceText);
	FinishPositionNumberList.Add(SeventhPlaceText);
	FinishPositionNumberList.Add(EighthPlaceText);
	FinishPositionNumberList.Add(NinthPlaceText);
	FinishPositionNumberList.Add(TenthPlaceText);
	FinishPositionNumberList.Add(EleventhPlaceText);
	FinishPositionNumberList.Add(TwelfthPlaceText);
	FinishPositionNumberList.Add(ThirteenthPlaceText);
}

void URaceOverWidget::SetFinishPositionImage(TArray<UTexture2D*> Textures)
{

	for (int32 i = 0; i < Textures.Num(); i ++)
	{
		FinishPositionImageList[i]->SetVisibility(ESlateVisibility::Visible);
		FinishPositionImageList[i]->SetBrushFromTexture(Textures[i]);
		FinishPositionNumberList[i]->SetVisibility(ESlateVisibility::Visible);
	}	
}

void URaceOverWidget::HideRaceOverCanvas()
{
	RaceOverCanvas->SetVisibility(ESlateVisibility::Hidden);
}