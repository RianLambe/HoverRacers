// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Create debug directional arrow
	DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + GetUpVector() * 100, 5, FColor::Blue);
	UArrowComponent* DebugArrow = CreateDefaultSubobject<UArrowComponent>("DebugArrow");
	DebugArrow->SetupAttachment(this);
	DebugArrow->SetRelativeRotation(GetUpVector().Rotation() * -1);
	
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	MainBody = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	ParentPodRacer = Cast<APodRacer>(GetOwner());
	
	//CollisionParameters.AddIgnoredActor(GetOwner());
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PodGroundCheck();
}

void UHoverComponent::PodGroundCheck() {
	//Adds force on impact if hover component requires hit
	if (RequireHit) {
		//Calculate start and end pos
		Start = GetComponentLocation();
		//End = Start + (-GetUpVector() * TraceLenght);
		End = Start + (FVector(0,0,-TraceLenght));



		//Do line trace
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility)) {
			//Debug
			if (DebugEnabled) {
				DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
				GEngine->AddOnScreenDebugMessage(-1, GetWorld()->DeltaTimeSeconds, FColor::Red, "Hit");
			}
			DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
			
			//GetOwner()->SetActorLocation(HitResult.Location + (HitResult.ImpactNormal * TraceLenght), false, nullptr, ETeleportType::TeleportPhysics);

			//FRotator test = FRotationMatrix::MakeFromXY(HitResult.ImpactNormal, GetOwner()->GetActorForwardVector());
			//GetOwner()->SetActorRotation(FRotationMatrix::MakeFromXY(HitResult.ImpactNormal, GetOwner()->GetActorForwardVector()));
			MainBody->SetLinearDamping(ParentPodRacer->GroundDrag);
			MainBody->SetAngularDamping(ParentPodRacer->GroundAngularDrag);
			MainBody->SetEnableGravity(false);
			ParentPodRacer->IsGrounded = true;

			GetOwner()->SetActorLocation(FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, HitResult.Location.Z + ParentPodRacer->RideHeight), false, nullptr, ETeleportType::ResetPhysics);

		}
		else {
			MainBody->SetLinearDamping(ParentPodRacer->AirDrag);
			MainBody->SetAngularDamping(ParentPodRacer->AirAngularDrag);
			MainBody->SetEnableGravity(true);
			ParentPodRacer->IsGrounded = false;
		}
	}
	else {
		//MainBody->AddImpulseAtLocation(GetUpVector() * HoverForce, GetComponentLocation());
		MainBody->AddImpulse(GetUpVector() * (ParentPodRacer->IsGrounded ? HoverForce : 0));

	}
}


