// Fill out your copyright notice in the Description page of Project Settings.


#include "TantrumnCharacterBase.h"

// Sets default values
ATantrumnCharacterBase::ATantrumnCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATantrumnCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATantrumnCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATantrumnCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATantrumnCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	APlayerController* PlayerController = GetController<APlayerController>();

	if (PlayerController)
	{
		const float fallImpactSpeed = FMath::Abs(GetVelocity().Z);
		if (fallImpactSpeed < MinImpactSpeed)
		{
			return;
		}

		const float DeltaImpact = MaxImpactSpeed - MinImpactSpeed;
		const float FallRatio = FMath::Clamp((fallImpactSpeed - MinImpactSpeed) / DeltaImpact, 0.0f, 1.0f);
		const bool bAffectSmall = FallRatio <= 0.5f;
		const bool bAffectLarge = FallRatio > 0.5f;

		PlayerController->PlayDynamicForceFeedback(FallRatio, 2.5f, bAffectLarge, bAffectSmall, bAffectLarge, bAffectSmall);
	}
}

