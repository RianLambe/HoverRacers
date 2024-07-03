// Copyright Epic Games, Inc. All Rights Reserved.

#include "PodRacingGameMode.h"
#include "PodRacingCharacter.h"
#include "SpectatorWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/SUserWidget.h"

void APodRacingGameMode::BeginPlay() {
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APodRacer::StaticClass(), AllRacers);

	//ChangeSpectator(true);

	USpectatorWidget* NewWidget = CreateWidget<USpectatorWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	NewWidget->AddToViewport();
}

APodRacingGameMode::APodRacingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

//Changes the current spectator the player is viewing
APawn* APodRacingGameMode::ChangeSpectator(bool Increment, int Index) {

	APodRacingGameMode* MyGameMode = Cast<APodRacingGameMode>(UGameplayStatics::GetGameMode(this));

	if (Index == -1) {
		if (Increment)	MyGameMode->SpectatorIndex++;
		else MyGameMode->SpectatorIndex--;
	}
	else {
		SpectatorIndex = 0;
	}
	
	APawn* NewPawn = Cast<APawn>(MyGameMode->AllRacers[FMath::Abs(MyGameMode->SpectatorIndex) % MyGameMode->AllRacers.Num()]);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(NewPawn);

	return NewPawn;
}


