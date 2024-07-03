// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "Math/Vector2D.h"
#include "Components/SkeletalMeshComponent.h"
#include "Physics/NetworkPhysicsComponent.h"
#include "PodRacer.generated.h"

USTRUCT(BlueprintType)
struct FRaceGhost {
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float FinishTime = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int StartingPosition = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FString RacerName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FTransform> GhostTransform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FVector2D> GhostYawThrottle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FVector2D> GhostRollPitch;
};

UENUM(BlueprintType)
enum class AbilityModes : uint8{
	Blaster,
	Boost
};

UCLASS()
class PODRACING_API APodRacer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APodRacer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Hover related vars
	void Hover();
	FVector Start;
	FVector End;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	
	FVector CalculatedVelocity;
	FRotator TiltRotation;
	 
	FTransform InitTransform;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Input
	UFUNCTION(BlueprintCallable) void AddPodInput(FVector2D YawThrottle, FVector2D RollPitch);
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D YawThrottleI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D RollPitchI;
	
	//Lap related functions / variables
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void Record(bool Record);
	UFUNCTION(BlueprintCallable) void AddLapTime();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float CurrentLapTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float GameStartTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<float> LapTimes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FRaceGhost RecordedGhost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float RecordingPullingRate = 0.01;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Lap settings") FString PlayerName;
	
	//Blaster
	UFUNCTION(BlueprintCallable) void UseBlasters();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<USceneComponent*> BlasterLocations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float BlasterAmmo = 50;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) AbilityModes AbilityMode;

	
	//Control related
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool CanMove = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float BoostAmount;
	float ForwardMultiplier = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool UsingBoost = false;
	UFUNCTION(BlueprintCallable) void UseBoost(bool Use);
	UFUNCTION(BlueprintCallable) void RestartGame();
	UFUNCTION(BlueprintCallable) void TiltPod(FVector2D RollPitchInput);
	UFUNCTION(BlueprintCallable) void YawControl(FVector2D YawThrottleInput, FVector2D RollPitchInput);
	UFUNCTION(BlueprintCallable) void PodMovement(FVector2D YawThrottleInput, FVector2D RollPitchInput);

	//Created components
	//UPROPERTY(BlueprintReadWrite) UNiagaraSystem* LeftEngineParticals; 
	
	//Visual
	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION(BlueprintCallable) void TiltEngines();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* PodRoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) USkeletalMeshComponent* PodMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) USceneComponent* LeftEngineParent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) USkeletalMeshComponent* LeftEngine;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) USceneComponent* RightEngineParent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) USkeletalMeshComponent* RightEngine;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector EngineParentOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector EngineOffset = FVector(0, 650, 0);
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float PodRoll = 70;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float PodPitch = 5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D EngineTiltRange = FVector2D(10.0f, 70.0f);
	UFUNCTION(BlueprintCallable) void ChangeCamera(int NewCameraIndex);

	//Player settings
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float GlobalControlSensitivity = 10;



	//Flight settings
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float ForwardForce = 4000000.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float JoystickForce = 300000.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float RideHeight = 300;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float GroundCheckDistance = 5000;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float GroundDrag = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float GroundAngularDrag = 4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float AirDrag = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Flight settings") float AirAngularDrag = 1;

	//Misc
	UPROPERTY(BlueprintReadOnly) float PodSpeed;
	UPROPERTY(BlueprintReadOnly) bool IsGrounded;
	UPROPERTY(BlueprintReadWrite) bool IsGhost = false;
	float TargetYaw;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
