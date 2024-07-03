// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PodRacer.h"
#include "Components/SceneComponent.h"
#include "HoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PODRACING_API UHoverComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FHitResult HitResult;
	FVector Start;
	FVector End;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	APodRacer* ParentPodRacer;

	//FCollisionQueryParams CollisionParameters;

	
	UFUNCTION(BlueprintCallable) void PodGroundCheck();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float TraceLenght = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float HoverForce = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool RequireHit = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool DebugEnabled = false;
	USkeletalMeshComponent* MainBody;
};
