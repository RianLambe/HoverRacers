// Fill out your copyright notice in the Description page of Project Settings.


#include "RacerSaves.h"

//Adds a saved ghost to the array in the correct order
void URacerSaves::AddGhost(FRaceGhost NewGhost) {
	for (int i = 0; i < SavedGhosts.Num(); i++) {
		if (NewGhost.FinishTime < SavedGhosts[i].FinishTime) {
			SavedGhosts.Insert(NewGhost, i);
			return;
		}
	}

	SavedGhosts.Add(NewGhost);
}
