// Fill out your copyright notice in the Description page of Project Settings.


#include "PodRacer.h"

#include "EnhancedInputComponent.h"
#include "HoverComponent.h"
#include "MovieSceneSequenceID.h"
//#include "ToolContextInterfaces.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PodRacing/PodRacingGameMode.h"
#include "ProfilingDebugging/BootProfiling.h"

// Sets default values
APodRacer::APodRacer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionParams.AddIgnoredActor(this);
	
	//Create root
	PodRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = PodRoot;


	//Create left engine
	LeftEngineParent = CreateDefaultSubobject<USceneComponent>(TEXT("Left engine parent"));
	LeftEngineParent->SetupAttachment(PodRoot);
	
	LeftEngine = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left engine"));
	LeftEngine->SetupAttachment(LeftEngineParent);
	//LeftEngineParticals = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Left engine particals")); // Particals
	//LeftEngineParticals->SetupAttachment(RightEngineParent);
	
	//Create right engine 
	RightEngineParent = CreateDefaultSubobject<USceneComponent>(TEXT("Right engine parent")); // Engine Parent
	RightEngineParent->SetupAttachment(PodRoot);
	RightEngine = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right engine")); // Engine 
	RightEngine->SetupAttachment(RightEngineParent);



	//Create blaster locations
	BlasterLocations.Add(CreateDefaultSubobject<USceneComponent>("Blaster location 1"));
	BlasterLocations[0]->SetupAttachment(PodMesh);
	BlasterLocations.Add(CreateDefaultSubobject<USceneComponent>("Blaster location 2"));
	BlasterLocations[1]->SetupAttachment(PodMesh);
	
	//Cretae visual pod mesh
	PodMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pod"));
	PodMesh->SetupAttachment(PodRoot);
}

//Called before tick
void APodRacer::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	//Sets engine positions
	LeftEngineParent->SetRelativeLocation(FVector(EngineParentOffset.X, EngineParentOffset.Y,EngineParentOffset.Z));
	LeftEngine->SetRelativeLocation(FVector(EngineOffset.X, -EngineOffset.Y,EngineOffset.Z));
	
	RightEngineParent->SetRelativeLocation(FVector(EngineParentOffset.X, -EngineParentOffset.Y,EngineParentOffset.Z));
	RightEngine->SetRelativeLocation(FVector(EngineOffset.X, EngineOffset.Y,EngineOffset.Z));

}





// Called when the game starts or when spawned
void APodRacer::BeginPlay() {
	Super::BeginPlay();
	InitTransform = GetActorTransform();
	APawn* MyPawn = Cast<APawn>(GetOwner());
}

// Called every frame
void APodRacer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	PodSpeed = GetVelocity().Length() * 0.036;
	
	if (!IsGhost) {
		Hover();
		PodMovement(YawThrottleI, RollPitchI);
		YawControl(YawThrottleI, RollPitchI);
		TiltPod(RollPitchI);
		TiltEngines();
	}
	
	
	//If using boost decrement the boost amount
	if(UsingBoost) {
		BoostAmount = FMathf::Clamp(BoostAmount - GetWorld()->GetDeltaSeconds() / 2, 0, 1);

		if (BoostAmount <= 0 ) UseBoost(false);
	}

	//Add blaster ammo over time
	BlasterAmmo = FMathf::Clamp(BlasterAmmo + GetWorld()->GetDeltaSeconds() * 2, 0, 100);
}

void APodRacer::AddPodInput(FVector2D YawThrottle, FVector2D RollPitch) {
	YawThrottleI = YawThrottle;
	RollPitchI = RollPitch;
}

// Called to bind functionality to input
void APodRacer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//Sets the player back to the start position
void APodRacer::RestartGame() {
	//Resets position and rotation
	PodRoot->SetPhysicsLinearVelocity(FVector::Zero());
	PodRoot->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
	SetActorTransform(InitTransform);

	//Resets timerS
	LapTimes.Empty();
	CurrentLapTime = GetWorld()->GetTimeSeconds();
	GameStartTime = GetWorld()->GetTimeSeconds();

}

//Keeps the pod at the correct height above the ground
void APodRacer::Hover() {
	//Calculate start and end pos
	Start = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z);
	End = Start + (FVector(0,0,-RideHeight - 500));
	
	FRotator TargetRotation;
	
	//Do line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams)) {
		//Sets physics settings
		PodRoot->SetLinearDamping(GroundDrag);
		PodRoot->SetAngularDamping(GroundAngularDrag);
		PodRoot->SetEnableGravity(false);
		IsGrounded = true;

		//Lerps to the new location and rotation
		TargetRotation = FMath::RInterpTo(GetActorRotation(), FRotationMatrix::MakeFromZX(HitResult.Normal, GetActorForwardVector()).Rotator(), GetWorld()->DeltaTimeSeconds, 2);
		FVector TargetP = FMath::VInterpTo(GetActorLocation(), HitResult.ImpactPoint + GetActorUpVector() * RideHeight, GetWorld()->DeltaTimeSeconds, 10);

		SetActorLocation(HitResult.ImpactPoint + GetActorUpVector() * RideHeight, false, nullptr, ETeleportType::ResetPhysics);
	}
	else {
		//Sets physics settings
		PodRoot->SetLinearDamping(AirDrag);
		PodRoot->SetAngularDamping(AirAngularDrag);
		PodRoot->SetEnableGravity(true);
		IsGrounded = false;

		TargetRotation = FMath::RInterpTo(GetActorRotation(), FRotationMatrix::MakeFromZX(FVector::UpVector, GetActorForwardVector()).Rotator(), GetWorld()->DeltaTimeSeconds, 2);
	}

	//Sets the actor rotation 
	SetActorRotation(TargetRotation, ETeleportType::TeleportPhysics);
}

//Adds the pods movement in all 4 directions
void APodRacer::PodMovement(FVector2D YawThrottleInput, FVector2D RollPitchInput) {

	if(!CanMove) return;
		
	CalculatedVelocity =
		(RollPitchI.X * JoystickForce * GetActorRightVector() +
		RollPitchI.Y * JoystickForce * GetActorForwardVector() +
		YawThrottleI.Y * ForwardForce * GetActorForwardVector() * ForwardMultiplier) *
		GetWorld()->DeltaTimeSeconds;
	
	PodRoot->AddImpulse(IsGrounded ? CalculatedVelocity : FVector::Zero());
}

//Tilts the pod on mesh on the pitch and roll axis
void APodRacer::TiltPod(FVector2D RollPitchInput) {

	if(CanMove && Cast<APodRacingGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->SpectatorModeEnabled) return;

	TiltRotation = FMath::RInterpTo(
		PodMesh->GetRelativeRotation(),
		FRotator(RollPitchInput.Y * PodPitch * -1,0,RollPitchInput.X * PodRoll),
		GetWorld()->GetDeltaSeconds(),
		3);

	PodMesh->SetRelativeRotation(TiltRotation, false, nullptr, ETeleportType::ResetPhysics);
}

//Controls the pods yaw 
void APodRacer::YawControl(FVector2D YawThrottleInput, FVector2D RollPitchInput) {

	if(!CanMove) return;

	//Calculate weighted input to yaw
	TargetYaw = FMath::FInterpTo(TargetYaw, ((RollPitchInput.X * 300.6) + (YawThrottleInput.X * 400)) * GlobalControlSensitivity, GetWorld()->GetDeltaSeconds(), 4);

	//Rotates the player on the yaw axis
	AddActorLocalRotation(FRotator(0,TargetYaw,0)  * GetWorld()->DeltaTimeSeconds, false , nullptr, ETeleportType::TeleportPhysics);
}

//Adds tilt to the engines
void APodRacer::TiltEngines() {
	//Calculate right engine parent tilt
	FRotator RightTarget = FMath::RInterpTo(
		RightEngineParent->GetRelativeRotation(),
		FRotator(
			0,
			RollPitchI.X * 20,
			FMath::Clamp(RollPitchI.X* EngineTiltRange.Y, EngineTiltRange.Y * -1, EngineTiltRange.X)),
		GetWorld()->DeltaTimeSeconds,
		3);

	FRotator LeftTarget = FMath::RInterpTo(
	LeftEngineParent->GetRelativeRotation(),
	FRotator(
		0,
		RollPitchI.X * 20,
		FMath::Clamp(RollPitchI.X * EngineTiltRange.Y, EngineTiltRange.X * -1, EngineTiltRange.Y)),
	GetWorld()->DeltaTimeSeconds,
	3);
	
	//Calculate left engine parent tilt
	FRotator EngineTiltTarget = FMath::RInterpTo(LeftEngineParent->GetRelativeRotation(),RollPitchI.X < 0 ?
		FRotator(FMath::Abs(RollPitchI.X) * 10,YawThrottleI.X* 15,0) :
		FRotator(0,0,0),
		GetWorld()->DeltaTimeSeconds,
		3);

	//Tilt engine parents
	RightEngineParent->SetRelativeRotation(RightTarget);
	LeftEngineParent->SetRelativeRotation(LeftTarget);

	//Tilt engines 
	RightEngine->SetRelativeRotation(EngineTiltTarget);
	LeftEngine->SetRelativeRotation(EngineTiltTarget);

}

//Adds a new lap time to the list
void APodRacer::AddLapTime() {
	LapTimes.Add(GetWorld()->GetTimeSeconds() - CurrentLapTime);

	CurrentLapTime = GetWorld()->GetTimeSeconds();
}

//Uses the blasters if equiped
void APodRacer::UseBlasters() {
	BlasterAmmo = BlasterAmmo - 10;
}

void APodRacer::ChangeCamera(int NewCameraIndex)
{
	
}

void APodRacer::UseBoost(bool Use) {
	UsingBoost = Use;
	ForwardMultiplier = Use? 1.5 : 1;
}
