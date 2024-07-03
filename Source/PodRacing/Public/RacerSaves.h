// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PodRacer.h"
#include "GameFramework/SaveGame.h"
#include "RacerSaves.generated.h"

/**
 * 
 */
UCLASS()
class PODRACING_API URacerSaves : public USaveGame
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FRaceGhost> SavedGhosts;

	UFUNCTION(BlueprintCallable) void AddGhost(FRaceGhost NewGhost);
	
};
