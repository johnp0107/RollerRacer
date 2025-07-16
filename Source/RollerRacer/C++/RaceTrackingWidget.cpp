// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceTrackingWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"

void URaceTrackingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PauseMenuTextList.Add(ContinueTextBlock);
	PauseMenuTextList.Add(OptionsTextBlock);
	PauseMenuTextList.Add(QuitTextBlock);

	FinishedRaceTextList.Add(MainMenuTextBlock);
	FinishedRaceTextList.Add(QuitTextBlock);
}

void URaceTrackingWidget::SetPositionText(FString PositionText)
{
	if (PositionTextBlock)
	{
		PositionTextBlock->SetColorAndOpacity(FLinearColor::Red);
		FSlateFontInfo FontInfo = PositionTextBlock->GetFont();
		FontInfo.Size = 32;
		PositionTextBlock->SetFont(FontInfo);
		PositionTextBlock->SetText(FText::FromString("Position: " + PositionText));
		PositionTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void URaceTrackingWidget::SetSpeedText(FString SpeedText)
{
	if (SpeedTextBlock)
	{
		SpeedTextBlock->SetColorAndOpacity(FLinearColor::Red);
		FSlateFontInfo FontInfo = SpeedTextBlock->GetFont();
		FontInfo.Size = 32;
		SpeedTextBlock->SetFont(FontInfo);
		SpeedTextBlock->SetText(FText::FromString("Speed: " + SpeedText));
		SpeedTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void URaceTrackingWidget::DisplayWrongWayText(bool DisplayText)
{
	if (WrongWayTextBlock)
	{
		WrongWayTextBlock->SetColorAndOpacity(FLinearColor::Red);
		FSlateFontInfo FontInfo = WrongWayTextBlock->GetFont();
		FontInfo.Size = 64;
		WrongWayTextBlock->SetFont(FontInfo);
		WrongWayTextBlock->SetText(FText::FromString("Wrong Way"));
	}
	if (DisplayText)
	{
		WrongWayTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		WrongWayTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}


void URaceTrackingWidget::SetLapText(FString LapText, FString MaxLaps)
{
	if (LapTextBlock)
	{
		LapTextBlock->SetColorAndOpacity(FLinearColor::Red);
		FSlateFontInfo FontInfo = LapTextBlock->GetFont();
		FontInfo.Size = 32;
		LapTextBlock->SetFont(FontInfo);
		LapTextBlock->SetText(FText::FromString("Lap: " + LapText + " / " + MaxLaps));
		LapTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void URaceTrackingWidget::SetRaceCountdownText(FString CountdownText)
{
	if (CountdownTextBlock)
	{
		CountdownTextBlock->SetColorAndOpacity(FLinearColor::Blue);
		FSlateFontInfo FontInfo = CountdownTextBlock->GetFont();
		FontInfo.Size = 120;
		CountdownTextBlock->SetFont(FontInfo);
		CountdownTextBlock->SetText(FText::FromString(CountdownText));
		CountdownTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void URaceTrackingWidget::SetPositionImages(TArray<UTexture2D*> Textures)
{
	if (FirstPlaceImage)
	{
		FirstPlaceImage->SetVisibility(ESlateVisibility::Visible);
		FirstPlaceImage->SetBrushFromTexture(Textures[0]);
		FirstPlaceText->SetVisibility(ESlateVisibility::Visible);
	}
	if (Textures.Num() > 1)
	{
		if (SecondPlaceImage)
		{
			SecondPlaceImage->SetVisibility(ESlateVisibility::Visible);
			SecondPlaceImage->SetBrushFromTexture(Textures[1]);
			SecondPlaceText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (Textures.Num() > 2)
	{
		if (ThirdPlaceImage)
		{
			ThirdPlaceImage->SetVisibility(ESlateVisibility::Visible);
			ThirdPlaceImage->SetBrushFromTexture(Textures[2]);
			ThirdPlaceText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (Textures.Num() > 3)
	{
		if (ForthPlaceImage)
		{
			ForthPlaceImage->SetVisibility(ESlateVisibility::Visible);
			ForthPlaceImage->SetBrushFromTexture(Textures[3]);
			ForthPlaceText->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void URaceTrackingWidget::HighlightPauseMenuText(int32 TextToHighlight)
{
	for (int32 i = 0; i < PauseMenuTextList.Num(); i++)
	{
		if (i == TextToHighlight)
		{
			FSlateFontInfo FontInfo = PauseMenuTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Bold");
			PauseMenuTextList[i]->SetFont(FontInfo);
		}
		else
		{
			FSlateFontInfo FontInfo = PauseMenuTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Light");
			PauseMenuTextList[i]->SetFont(FontInfo);
		}
	}
}

void URaceTrackingWidget::HighlightFinishedRaceMenuText(int32 TextToHighlight)
{
	for (int32 i = 0; i < FinishedRaceTextList.Num(); i++)
	{
		if (i == TextToHighlight)
		{
			FSlateFontInfo FontInfo = FinishedRaceTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Bold");
			FinishedRaceTextList[i]->SetFont(FontInfo);
		}
		else
		{
			FSlateFontInfo FontInfo = FinishedRaceTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Light");
			FinishedRaceTextList[i]->SetFont(FontInfo);
		}
	}
}

