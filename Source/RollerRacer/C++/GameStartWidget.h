// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "CaptureTextureSnapshot.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Components/HorizontalBox.h"
#include "FileMediaSource.h"
#include "GameStartWidget.generated.h"


UCLASS()
class ROLLERRACER_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> StartScreenMainCanvas;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GameTitleTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BackTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>ConfirmTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SinglePlayerTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MultiplayerTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CreditsTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ExitTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TArray<TObjectPtr<UTextBlock>> StartMenuTextList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SelectRacerTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SelectRacerDesignTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SelectTrackTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ComingSoonTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SelectNumberOfComputerTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SelectNumberOfLapsTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TArray<TObjectPtr<UTextBlock>> RacerSelectionTextList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TArray<TObjectPtr<UTextBlock>> TrackSelectionTextList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>PlayerChosenAIPlayerTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock>PlayerChosenNumberOfLapsTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage>TrackSelectionImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* LeftArrowImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* RightArrowImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage>MovieImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
	UMediaSource* MediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
	UMediaTexture* MediaTexture;

	UPROPERTY()
	UCaptureTextureSnapshot* CaptureTexture;

	void SetTrackSelectionImage(UTexture2D* Texture);

	void HighlightRacerSelectionText(int32 TextToHighlight);

	void HighlightTrackSelectionText(int32 TextToHighlight);

	void ChangeNumberOfAIPlayersText(FString NumberOfAIPlayersText);

	void ChangeNumberOfLapsText(FString NumberOfLapsText);

	void HighlightStartMenuText(int32 TextToHighlight);
};
