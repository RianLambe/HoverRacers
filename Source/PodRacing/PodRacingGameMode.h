// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PodRacer.h"
//#include "UnrealWidgetFwd.h"
#include "GameFramework/GameModeBase.h"
#include "PodRacingGameMode.generated.h"

UCLASS(minimalapi)
class APodRacingGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	
public:
	APodRacingGameMode();
	
	UFUNCTION(BlueprintCallable) APawn* ChangeSpectator(bool Increment, int Index);
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FString SaveGameToUse;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool SpectatorModeEnabled;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FTransform> StartingPositions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<AActor*> AllRacers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int CurrentRecordingIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool ShouldUpdateRecordingIndex = true;
	int SpectatorIndex;
	UPROPERTY(EditAnywhere) int GateIndex = 1;
};



