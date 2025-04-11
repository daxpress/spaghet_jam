// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuUserWidget::LoadLevelAsync()
{
	// Using LoadPackageAsync to implement the loading screen
	LoadPackageAsync(TEXT("/Game/Maps/Game_Map/Game_Map"),
	                 FLoadPackageAsyncDelegate::CreateLambda([this] (const FName&PackageName, UPackage * LoadedPackage,
	                                                         EAsyncLoadingResult::Type Result)
	{
		if (Result == EAsyncLoadingResult::Succeeded)
		{
			UGameplayStatics::OpenLevel(GetOwningPlayer(), TEXT("Game_Map"));
		}
	}
	)
	,
	0,
		PKG_ContainsMap
	)
	;
}

