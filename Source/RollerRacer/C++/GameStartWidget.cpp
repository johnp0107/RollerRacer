// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
//#include "Blueprint/WidgetLayoutLibrary.h"

void UGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (MediaPlayer && MediaSource)
	{
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

	RacerSelectionTextList.Add(SelectRacerTextBlock);
	RacerSelectionTextList.Add(SelectRacerDesignTextBlock);
	TrackSelectionTextList.Add(SelectTrackTextBlock);
	TrackSelectionTextList.Add(SelectNumberOfLapsTextBlock);
	TrackSelectionTextList.Add(SelectNumberOfComputerTextBlock);
}

void UGameStartWidget::HighlightRacerSelectionText(int32 TextToHighlight)
{
	for (int32 i = 0; i < RacerSelectionTextList.Num(); i++)
	{
		if (i == TextToHighlight)
		{
			FSlateFontInfo FontInfo = RacerSelectionTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Bold");
			RacerSelectionTextList[i]->SetFont(FontInfo);
		}
		else
		{
			FSlateFontInfo FontInfo = RacerSelectionTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Light");
			RacerSelectionTextList[i]->SetFont(FontInfo);
		}
	}
}

void UGameStartWidget::HighlightTrackSelectionText(int32 TextToHighlight)
{
	for (int32 i = 0; i < TrackSelectionTextList.Num(); i++)
	{
		if (i == TextToHighlight)
		{
			FSlateFontInfo FontInfo = TrackSelectionTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Bold");
			TrackSelectionTextList[i]->SetFont(FontInfo);
		}
		else
		{
			FSlateFontInfo FontInfo = TrackSelectionTextList[i]->Font;
			FontInfo.TypefaceFontName = FName("Light");
			TrackSelectionTextList[i]->SetFont(FontInfo);
		}
	}
}

void UGameStartWidget::ChangeNumberOfAIPlayersText(FString NumberOfAIPlayersText)
{
	if (PlayerChosenAIPlayerTextBlock)
	{
		FSlateFontInfo FontInfo = PlayerChosenAIPlayerTextBlock->GetFont();
		PlayerChosenAIPlayerTextBlock->SetText(FText::FromString(NumberOfAIPlayersText));
		PlayerChosenAIPlayerTextBlock->SetJustification(ETextJustify::Center);
	}
}

void UGameStartWidget::ChangeNumberOfLapsText(FString NumberOfLapsText)
{
	if (PlayerChosenNumberOfLapsTextBlock)
	{
		FSlateFontInfo FontInfo = PlayerChosenNumberOfLapsTextBlock->GetFont();
		PlayerChosenNumberOfLapsTextBlock->SetText(FText::FromString(NumberOfLapsText));
		PlayerChosenNumberOfLapsTextBlock->SetJustification(ETextJustify::Center);
	}
}

void UGameStartWidget::SetTrackSelectionImage(UTexture2D* Texture)
{
	if (TrackSelectionImage)
	{
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

