// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MediaPlayer && MediaSource)
	{
		MediaPlayer->OpenSource(MediaSource);

		if (UMaterialInstanceDynamic* MaterialInstance = MovieImage->GetDynamicMaterial())
		{
			MediaTexture = NewObject<UMediaTexture>();
			MediaTexture->SetMediaPlayer(MediaPlayer);
			MaterialInstance = MovieImage->GetDynamicMaterial();
			MaterialInstance->SetTextureParameterValue(FName("MyMediaTexture"), MediaTexture);
		}
	}

	StartMenuTextList.Add(SinglePlayerTextBlock);
	StartMenuTextList.Add(MultiplayerTextBlock);
	StartMenuTextList.Add(CreditsTextBlock);
	StartMenuTextList.Add(ExitTextBlock);

	RaceSelectionTextList.Add(SelectRacerTextBlock);
	RaceSelectionTextList.Add(SelectRacerDesignTextBlock);
	RaceSelectionTextList.Add(SelectTrackTextBlock);
	RaceSelectionTextList.Add(AIRacerNumberTextBlock);
}

void UGameStartWidget::HighlightRaceSelectionText(int32 TextToHighlight)
{
	for (int32 i = 0; i < RaceSelectionTextList.Num(); i++)
	{
		if (i == TextToHighlight)
		{
			FSlateFontInfo FontInfo = RaceSelectionTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Bold");
			RaceSelectionTextList[i]->SetFont(FontInfo);
		}
		else
		{
			FSlateFontInfo FontInfo = RaceSelectionTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Light");
			RaceSelectionTextList[i]->SetFont(FontInfo);
		}
	}
}

void UGameStartWidget::ChangeNumberOfAIPlayersText(FString NumberOfAIPlayersText)
{
	if (NumberOfAIPlayers)
	{
		FSlateFontInfo FontInfo = NumberOfAIPlayers->GetFont();
		FontInfo.Size = 72;
		NumberOfAIPlayers->SetText(FText::FromString(NumberOfAIPlayersText));
		NumberOfAIPlayers->SetJustification(ETextJustify::Center);
	}
}

void UGameStartWidget::SetTrackSelectionImage(UTexture2D* Texture)
{
	if (TrackSelectionImage)
	{
		//PlayerSelectionImage->SetVisibility(ESlateVisibility::Visible);
		TrackSelectionImage->SetBrushFromTexture(Texture);
	}
}

void UGameStartWidget::HighlightStartMenuText(int32 TextToHighlight)
{
	for (int32 i = 0; i < StartMenuTextList.Num(); i++)
	{
		if (i == TextToHighlight)
		{
			FSlateFontInfo FontInfo = StartMenuTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Bold");
			StartMenuTextList[i]->SetFont(FontInfo);
		}
		else
		{
			FSlateFontInfo FontInfo = StartMenuTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Light");
			StartMenuTextList[i]->SetFont(FontInfo);
		}
	}
}
