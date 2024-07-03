// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"

#include "PodRacer.h"
#include "Kismet/GameplayStatics.h"
#include "PodRacing/PodRacingGameMode.h"

// Sets default values
ATrack::ATrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Finish = CreateDefaultSubobject<UBoxComponent>("Finish line");
	RootComponent = Finish;

}

// Called when the game starts or when spawned
void ATrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrack::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Finish->OnComponentBeginOverlap.AddDynamic(this, &ATrack::OnOverlapBegin);
	Finish->OnComponentEndOverlap.AddDynamic(this, &ATrack::OnOverlapEnd);

}
//Overlap end event
void ATrack::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	CanOverlap = true;
}

//Overlap event
void ATrack::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	APodRacer* RacerRef = Cast<APodRacer>(OtherActor); // reference to pod racer character
	APodRacingGameMode* MyGameMode = Cast<APodRacingGameMode>(UGameplayStatics::GetGameMode(this));
	
	if (RacerRef->IsPawnControlled() && CanOverlap && MyGameMode->GateIndex % 2 == GateNum) {
		CanOverlap = false; //To stop multiple overlap events every frame
		MyGameMode->GateIndex++;

		if (GateNum ==0) RacerRef->AddLapTime(); //Adds lap times


		//Stop recording if the player has completed the final lap
		if(RacerRef->LapTimes.Num() >= 3) {
			RacerRef->Record(false);
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);
		}
	}
}


